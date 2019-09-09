/******************************************************************************
 *
 *  Copyright (C) 2014 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#define LOG_TAG "bt_hci_h5"

#include <assert.h>
#include <errno.h>
#include <string.h>

#include "osi/include/eager_reader.h"
#include "hci_hal.h"
#include "osi/include/osi.h"
#include "osi/include/log.h"
#include "osi/include/reactor.h"
#include "osi/include/thread.h"
#include "vendor.h"

#include "hci_layer.h"
#include "hci_h5_int.h"

#define HCI_HAL_SERIAL_BUFFER_SIZE 1026
#define HCI_BLE_EVENT 0x3e

// Increased HCI thread priority to keep up with the audio sub-system
// when streaming time sensitive data (A2DP).
#define HCI_THREAD_PRIORITY -19

// Our interface and modules we import
static const hci_hal_t h5_interface;
static const hci_h5_t* h5_int_interface;
static const hci_hal_callbacks_t *h5_hal_callbacks;
static const vendor_t *h5_vendor;

static thread_t *thread; // Not owned by us

static int uart_fd;
static eager_reader_t *uart_stream;
static serial_data_type_t current_data_type;
static bool stream_has_interpretation;
static bool stream_corruption_detected;
static uint8_t stream_corruption_bytes_to_ignore;

static void h5_data_ready_cb(serial_data_type_t type);
static uint16_t h5_int_transmit_data_cb(serial_data_type_t type, uint8_t *data, uint16_t length) ;
static void h5_event_uart_has_bytes(eager_reader_t *reader, void *context);

static  hci_h5_hal_callbacks_t h5_int_hal_callbacks = {
    .h5_int_transmit_data_cb = h5_int_transmit_data_cb,
    .h5_data_ready_cb = h5_data_ready_cb,
};


// Interface functions

static bool h5_hal_init(const hci_hal_callbacks_t *upper_callbacks, thread_t *upper_thread) {
  assert(upper_callbacks != NULL);
  assert(upper_thread != NULL);

  h5_hal_callbacks = upper_callbacks;
  thread = upper_thread;
  h5_int_interface = hci_get_h5_int_interface();
  h5_int_interface->h5_int_init(&h5_int_hal_callbacks);
  return true;
}

static bool h5_hal_open() {
  LOG_INFO(LOG_TAG, "%s", __func__);
  // TODO(zachoverflow): close if already open / or don't reopen (maybe at the hci layer level)

  int fd_array[CH_MAX];
  int number_of_ports = h5_vendor->send_command(VENDOR_OPEN_USERIAL, &fd_array);

  if (number_of_ports != 1) {
    LOG_ERROR(LOG_TAG, "%s opened the wrong number of ports: got %d, expected 1.", __func__, number_of_ports);
    goto error;
  }

  uart_fd = fd_array[0];
  if (uart_fd == INVALID_FD) {
    LOG_ERROR(LOG_TAG, "%s unable to open the uart serial port.", __func__);
    goto error;
  }

  uart_stream = eager_reader_new(uart_fd, &allocator_malloc, HCI_HAL_SERIAL_BUFFER_SIZE, SIZE_MAX, "hci_single_channel");
  if (!uart_stream) {
    LOG_ERROR(LOG_TAG, "%s unable to create eager reader for the uart serial port.", __func__);
    goto error;
  }

  stream_has_interpretation = false;
  stream_corruption_detected = false;
  stream_corruption_bytes_to_ignore = 0;
  eager_reader_register(uart_stream, thread_get_reactor(thread), h5_event_uart_has_bytes, NULL);

  // Raise thread priorities to keep up with audio
  thread_set_priority(thread, HCI_THREAD_PRIORITY);
  thread_set_priority(eager_reader_get_read_thread(uart_stream), HCI_THREAD_PRIORITY);

  return true;

error:
  h5_interface.close();
  return false;
}

static void h5_hal_close() {
  LOG_INFO(LOG_TAG, "%s", __func__);

  eager_reader_free(uart_stream);
  h5_vendor->send_command(VENDOR_CLOSE_USERIAL, NULL);
  uart_fd = INVALID_FD;
  h5_int_interface->h5_int_cleanup();
}

static size_t h5_read_data(serial_data_type_t type, uint8_t *buffer, size_t max_size)
{
  int size = 0;
  if (type < DATA_TYPE_ACL || type > DATA_TYPE_EVENT) {
    LOG_ERROR(LOG_TAG, "%s invalid data type: %d", __func__, type);
    return 0;
  } else if (!stream_has_interpretation) {
    LOG_ERROR(LOG_TAG, "%s with no valid stream intepretation.", __func__);
    return 0;
  } else if (current_data_type != type) {
    LOG_ERROR(LOG_TAG, "%s with different type than existing interpretation.", __func__);
    return 0;
  }

  if(max_size == 0) {
    return 0;
  }
  size = h5_int_interface->h5_int_read_data(buffer, max_size);
  if(size == -1) {
    LOG_ERROR(LOG_TAG, "Error there is no data to be read, stack error or fw error!");
    return 0;
  }
  return size;
}

static void h5_packet_finished(serial_data_type_t type) {
  if (!stream_has_interpretation)
    LOG_ERROR(LOG_TAG, "%s with no existing stream interpretation.", __func__);
  else if (current_data_type != type)
    LOG_ERROR(LOG_TAG, "%s with different type than existing interpretation.", __func__);

  stream_has_interpretation = false;
}

uint16_t h5_int_transmit_data_cb(serial_data_type_t type, uint8_t *data, uint16_t length) {
      assert(data != NULL);
      assert(length > 0);

      //LOG_DEBUG(LOG_TAG, "hci_hal_h5 %s data type: %d", __func__, type);

      if (type != DATA_TYPE_H5) {
        LOG_ERROR(LOG_TAG, "%s invalid data type: %d", __func__, type);
        return 0;
      }

      uint16_t transmitted_length = 0;
      while (length > 0) {
        ssize_t ret = write(uart_fd, data + transmitted_length, length);
        switch (ret) {
          case -1:
            LOG_ERROR(LOG_TAG, "In %s, error writing to the uart serial port: %s", __func__, strerror(errno));
            goto done;
          case 0:
            // If we wrote nothing, don't loop more because we
            // can't go to infinity or beyond
            goto done;
          default:
            transmitted_length += ret;
            length -= ret;
            break;
        }
      }

done:;

      return transmitted_length;

}

static void h5_data_ready_cb(serial_data_type_t type)
{
    stream_has_interpretation = true;
    current_data_type = type;
    h5_hal_callbacks->data_ready(current_data_type);
}

static uint16_t h5_transmit_data(serial_data_type_t type, uint8_t *data, uint16_t length) {
    assert(data != NULL);
    assert(length > 0);

    uint16_t transmitted_length = 0;
    uint16_t opcode;
    uint8_t  *data_temp = data;
    //LOG_DEBUG(LOG_TAG, "hci_hal_h5 %s, data type: %d", __func__, type);

    if (type < DATA_TYPE_COMMAND || type > DATA_TYPE_SCO) {
        LOG_ERROR(LOG_TAG, "%s invalid data type: %d", __func__, type);
        return 0;
    }

    switch (type) {
    case DATA_TYPE_COMMAND:
        STREAM_TO_UINT16(opcode, data_temp);
        //LOG_DEBUG(LOG_TAG, "cmd opcode  = 0x%0x", opcode);
        if(opcode == HCI_VSC_H5_INIT)
        {
            transmitted_length = length;
            h5_int_interface->h5_send_sync_cmd(opcode, NULL, length);
            break;
        }
        transmitted_length = h5_int_interface->h5_send_cmd(type, data, length);
    break;

    case DATA_TYPE_ACL:
        transmitted_length = h5_int_interface->h5_send_acl_data(type, data, length);
    break;

    case DATA_TYPE_SCO:
        transmitted_length = h5_int_interface->h5_send_sco_data(type, data, length);
    break;

    default:
    break;
    }
    return transmitted_length;
}

// Internal functions

// WORKAROUND:
// As exhibited by b/23934838, during result-heavy LE scans, the UART byte
// stream can get corrupted, leading to assertions caused by mis-interpreting
// the bytes following the corruption.
// This workaround looks for tell-tale signs of a BLE event and attempts to
// skip the correct amount of bytes in the stream to re-synchronize onto
// a packet boundary.
// Function returns true if |byte_read| has been processed by the workaround.
static bool stream_corrupted_during_le_scan_workaround(const uint8_t byte_read)
{
  if (!stream_corruption_detected && byte_read == HCI_BLE_EVENT) {
    LOG_ERROR(LOG_TAG, "%s HCI stream corrupted (message type 0x3E)!", __func__);
    stream_corruption_detected = true;
    return true;
  }

  if (stream_corruption_detected) {
    if (stream_corruption_bytes_to_ignore == 0) {
      stream_corruption_bytes_to_ignore = byte_read;
      LOG_ERROR(LOG_TAG, "%s About to skip %d bytes...", __func__, stream_corruption_bytes_to_ignore);
    } else {
      --stream_corruption_bytes_to_ignore;
    }

    if (stream_corruption_bytes_to_ignore == 0) {
      LOG_ERROR(LOG_TAG, "%s Back to our regularly scheduled program...", __func__);
      stream_corruption_detected = false;
    }
    return true;
  }

  return false;
}

// See what data is waiting, and notify the upper layer
static void h5_event_uart_has_bytes(eager_reader_t *reader, UNUSED_ATTR void *context) {
    uint8_t data_buffer[10] = {0};
    size_t read_len = 0;
    BOOLEAN status = FALSE;
    read_len = eager_reader_read(reader, data_buffer, 10);
    if(read_len > 0)
        status = h5_int_interface->h5_recv_msg(data_buffer, read_len);
}

static const hci_hal_t h5_interface = {
  h5_hal_init,

  h5_hal_open,
  h5_hal_close,

  h5_read_data,
  h5_packet_finished,
  h5_transmit_data,
};

const hci_hal_t *hci_hal_h5_get_interface() {
  h5_vendor = vendor_get_interface();
  return &h5_interface;
}

const hci_hal_t *hci_hal_h5_get_test_interface(vendor_t *vendor_interface) {
  h5_vendor = vendor_interface;
  return &h5_interface;
}
