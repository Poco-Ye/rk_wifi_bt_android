/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
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

/************************************************************************************
 *
 *  Filename:      bluetooth.c
 *
 *  Description:   Bluetooth HAL implementation
 *
 ***********************************************************************************/

#define LOG_TAG "bt_btif"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <hardware/bluetooth.h>
#include <hardware/bt_av.h>
#include <hardware/bt_gatt.h>
#include <hardware/bt_hf.h>
#include <hardware/bt_hf_client.h>
#include <hardware/bt_hh.h>
#include <hardware/bt_hl.h>
#include <hardware/bt_mce.h>
#include <hardware/bt_pan.h>
#include <hardware/bt_rc.h>
#include <hardware/bt_sdp.h>
#include <hardware/bt_sock.h>

#include "bt_utils.h"
#include "btif_api.h"
#include "btif_debug.h"
#include "btsnoop.h"
#include "btsnoop_mem.h"
#include "device/include/interop.h"
#include "osi/include/allocation_tracker.h"
#include "osi/include/alarm.h"
#include "osi/include/log.h"
#include "osi/include/metrics.h"
#include "osi/include/osi.h"
#include "osi/include/wakelock.h"
#include "stack_manager.h"
#include "btif_config.h"
#include "btif_storage.h"
#include "btif/include/btif_debug_btsnoop.h"
#include "btif/include/btif_debug_conn.h"
#include "btif/include/btif_media.h"
#ifdef BLUETOOTH_RTK_API
#include <hardware/bt_rtkbt.h>
#endif
/************************************************************************************
**  Static variables
************************************************************************************/

bt_callbacks_t *bt_hal_cbacks = NULL;
bool restricted_mode = FALSE;

/************************************************************************************
**  Externs
************************************************************************************/

/* list all extended interfaces here */
#ifdef BLUETOOTH_RTK_API
extern volatile BOOLEAN uipc_inited;
#endif
/* handsfree profile */
extern bthf_interface_t *btif_hf_get_interface();
/* handsfree profile - client */
extern bthf_client_interface_t *btif_hf_client_get_interface();
/* advanced audio profile */
extern btav_interface_t *btif_av_get_src_interface();
extern btav_interface_t *btif_av_get_sink_interface();
/*rfc l2cap*/
extern btsock_interface_t *btif_sock_get_interface();
/* hid host profile */
extern bthh_interface_t *btif_hh_get_interface();
/* health device profile */
extern bthl_interface_t *btif_hl_get_interface();
/*pan*/
extern btpan_interface_t *btif_pan_get_interface();
/*map client*/
extern btmce_interface_t *btif_mce_get_interface();
#if BLE_INCLUDED == TRUE
/* gatt */
extern btgatt_interface_t *btif_gatt_get_interface();
#endif
/* avrc target */
extern btrc_interface_t *btif_rc_get_interface();
/* avrc controller */
extern btrc_interface_t *btif_rc_ctrl_get_interface();
/*SDP search client*/
extern btsdp_interface_t *btif_sdp_get_interface();
#ifdef BLUETOOTH_RTK_API
extern rtkbt_interface_t *btif_rtkbt_get_interface();
#endif

/************************************************************************************
**  Functions
************************************************************************************/

static bool interface_ready(void) {
  return bt_hal_cbacks != NULL;
}

static bool is_profile(const char *p1, const char *p2) {
  assert(p1);
  assert(p2);
  return strlen(p1) == strlen(p2) && strncmp(p1, p2, strlen(p2)) == 0;
}

/*****************************************************************************
**
**   BLUETOOTH HAL INTERFACE FUNCTIONS
**
*****************************************************************************/

static int init(bt_callbacks_t *callbacks) {
  LOG_INFO(LOG_TAG, "%s", __func__);

  if (interface_ready())
    return BT_STATUS_DONE;

#ifdef BLUEDROID_DEBUG
  allocation_tracker_init();
#endif

  bt_hal_cbacks = callbacks;
  stack_manager_get_interface()->init_stack();
  btif_debug_init();
#ifdef BLUETOOTH_RTK_API
  uipc_inited = FALSE;
#endif
  return BT_STATUS_SUCCESS;
}

static int enable(bool start_restricted) {
  LOG_INFO(LOG_TAG, "%s: start restricted = %d", __func__, start_restricted);

  restricted_mode = start_restricted;

  if (!interface_ready())
    return BT_STATUS_NOT_READY;

  stack_manager_get_interface()->start_up_stack_async();
  return BT_STATUS_SUCCESS;
}

static int disable(void) {
  if (!interface_ready())
    return BT_STATUS_NOT_READY;

  stack_manager_get_interface()->shut_down_stack_async();
  return BT_STATUS_SUCCESS;
}

static void cleanup(void) {
  stack_manager_get_interface()->clean_up_stack();
}

bool is_restricted_mode() {
  return restricted_mode;
}

static int get_adapter_properties(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_adapter_properties();
}

static int get_adapter_property(bt_property_type_t type)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_adapter_property(type);
}

static int set_adapter_property(const bt_property_t *property)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_set_adapter_property(property);
}

int get_remote_device_properties(bt_bdaddr_t *remote_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_remote_device_properties(remote_addr);
}

int get_remote_device_property(bt_bdaddr_t *remote_addr, bt_property_type_t type)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_remote_device_property(remote_addr, type);
}

int set_remote_device_property(bt_bdaddr_t *remote_addr, const bt_property_t *property)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_set_remote_device_property(remote_addr, property);
}

int get_remote_service_record(bt_bdaddr_t *remote_addr, bt_uuid_t *uuid)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_get_remote_service_record(remote_addr, uuid);
}

int get_remote_services(bt_bdaddr_t *remote_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_get_remote_services(remote_addr);
}

static int start_discovery(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_start_discovery();
}

static int cancel_discovery(void)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_cancel_discovery();
}

static int create_bond(const bt_bdaddr_t *bd_addr, int transport)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_create_bond(bd_addr, transport);
}

static int create_bond_out_of_band(const bt_bdaddr_t *bd_addr, int transport,
                                   const bt_out_of_band_data_t *oob_data)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_create_bond_out_of_band(bd_addr, transport, oob_data);
}

static int cancel_bond(const bt_bdaddr_t *bd_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_cancel_bond(bd_addr);
}

static int remove_bond(const bt_bdaddr_t *bd_addr)
{
    if (is_restricted_mode() && !btif_storage_is_restricted_device(bd_addr))
        return BT_STATUS_SUCCESS;

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_remove_bond(bd_addr);
}

static int get_connection_state(const bt_bdaddr_t *bd_addr)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return 0;

    return btif_dm_get_connection_state(bd_addr);
}

static int pin_reply(const bt_bdaddr_t *bd_addr, uint8_t accept,
                 uint8_t pin_len, bt_pin_code_t *pin_code)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_pin_reply(bd_addr, accept, pin_len, pin_code);
}

static int ssp_reply(const bt_bdaddr_t *bd_addr, bt_ssp_variant_t variant,
                       uint8_t accept, uint32_t passkey)
{
    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dm_ssp_reply(bd_addr, variant, accept, passkey);
}

static int read_energy_info()
{
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;
    btif_dm_read_energy_info();
    return BT_STATUS_SUCCESS;
}

static void dump(int fd, const char **arguments)
{
    if (arguments != NULL && arguments[0] != NULL) {
      if (strncmp(arguments[0], "--proto-text", 12) == 0) {
        btif_update_a2dp_metrics();
        metrics_print(fd, true);
        return;
      }
      if (strncmp(arguments[0], "--proto-bin", 11) == 0) {
        btif_update_a2dp_metrics();
        metrics_write(fd, true);
        return;
      }
    }
    btif_debug_conn_dump(fd);
    btif_debug_bond_event_dump(fd);
    btif_debug_a2dp_dump(fd);
    btif_debug_config_dump(fd);
    wakelock_debug_dump(fd);
    alarm_debug_dump(fd);
#if defined(BTSNOOP_MEM) && (BTSNOOP_MEM == TRUE)
    btif_debug_btsnoop_dump(fd);
#endif

    close(fd);
}

static const void* get_profile_interface (const char *profile_id)
{
    LOG_INFO(LOG_TAG, "get_profile_interface %s", profile_id);

    /* sanity check */
    if (interface_ready() == FALSE)
        return NULL;

    /* check for supported profile interfaces */
    if (is_profile(profile_id, BT_PROFILE_HANDSFREE_ID))
        return btif_hf_get_interface();

    if (is_profile(profile_id, BT_PROFILE_HANDSFREE_CLIENT_ID))
        return btif_hf_client_get_interface();

    if (is_profile(profile_id, BT_PROFILE_SOCKETS_ID))
        return btif_sock_get_interface();

    if (is_profile(profile_id, BT_PROFILE_PAN_ID))
        return btif_pan_get_interface();

    if (is_profile(profile_id, BT_PROFILE_ADVANCED_AUDIO_ID))
        return btif_av_get_src_interface();

    if (is_profile(profile_id, BT_PROFILE_ADVANCED_AUDIO_SINK_ID))
        return btif_av_get_sink_interface();

    if (is_profile(profile_id, BT_PROFILE_HIDHOST_ID))
        return btif_hh_get_interface();

    if (is_profile(profile_id, BT_PROFILE_HEALTH_ID))
        return btif_hl_get_interface();

    if (is_profile(profile_id, BT_PROFILE_SDP_CLIENT_ID))
        return btif_sdp_get_interface();

#if ( BTA_GATT_INCLUDED == TRUE && BLE_INCLUDED == TRUE)
    if (is_profile(profile_id, BT_PROFILE_GATT_ID))
        return btif_gatt_get_interface();
#endif

    if (is_profile(profile_id, BT_PROFILE_AV_RC_ID))
        return btif_rc_get_interface();

    if (is_profile(profile_id, BT_PROFILE_AV_RC_CTRL_ID))
        return btif_rc_ctrl_get_interface();
#ifdef BLUETOOTH_RTK_API
    if (is_profile(profile_id, BT_PROFILE_RTKBT_ID))
        return btif_rtkbt_get_interface();
#endif
    return NULL;
}

int dut_mode_configure(uint8_t enable)
{
    LOG_INFO(LOG_TAG, "dut_mode_configure");

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dut_mode_configure(enable);
}

int dut_mode_send(uint16_t opcode, uint8_t* buf, uint8_t len)
{
    LOG_INFO(LOG_TAG, "dut_mode_send");

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_dut_mode_send(opcode, buf, len);
}

#if BLE_INCLUDED == TRUE
int le_test_mode(uint16_t opcode, uint8_t* buf, uint8_t len)
{
    LOG_INFO(LOG_TAG, "le_test_mode");

    /* sanity check */
    if (interface_ready() == FALSE)
        return BT_STATUS_NOT_READY;

    return btif_le_test_mode(opcode, buf, len);
}
#endif

int config_hci_snoop_log(uint8_t enable)
{
    LOG_INFO(LOG_TAG, "config_hci_snoop_log");

    if (!interface_ready())
        return BT_STATUS_NOT_READY;

    btsnoop_get_interface()->set_api_wants_to_log(enable);
    return BT_STATUS_SUCCESS;
}

static int set_os_callouts(bt_os_callouts_t *callouts) {
    wakelock_set_os_callouts(callouts);
    return BT_STATUS_SUCCESS;
}

static int config_clear(void) {
    LOG_INFO(LOG_TAG, "%s", __func__);
    return btif_config_clear() ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}
#ifdef BLUETOOTH_RTK
static const bt_interface_t bluetoothInterface = {
    .size = sizeof(bluetoothInterface),
    .init = init,
    .enable = enable,
    .disable = disable,
    .cleanup = cleanup,
    .get_adapter_properties = get_adapter_properties,
    .get_adapter_property = get_adapter_property,
    .set_adapter_property = set_adapter_property,
    .get_remote_device_properties = get_remote_device_properties,
    .get_remote_device_property = get_remote_device_property,
    .set_remote_device_property = set_remote_device_property,
    .get_remote_service_record = get_remote_service_record,
    .get_remote_services = get_remote_services,
    .start_discovery = start_discovery,
    .cancel_discovery = cancel_discovery,
    .create_bond = create_bond,
    .create_bond_out_of_band = create_bond_out_of_band,
    .remove_bond = remove_bond,
    .cancel_bond = cancel_bond,
    .get_connection_state = get_connection_state,
    .pin_reply = pin_reply,
    .ssp_reply = ssp_reply,
    .get_profile_interface = get_profile_interface,
    .dut_mode_configure = dut_mode_configure,
    .dut_mode_send = dut_mode_send,
#if BLE_INCLUDED == TRUE
    .le_test_mode = le_test_mode,
#else
    .le_test_mode = NULL,
#endif
    .config_hci_snoop_log = config_hci_snoop_log,
    .set_os_callouts = set_os_callouts,
    .read_energy_info = read_energy_info,
    .dump = dump,
    .config_clear = config_clear,
    .interop_database_clear = interop_database_clear,
    .interop_database_add = interop_database_add,
};
#else
static const bt_interface_t bluetoothInterface = {
    sizeof(bluetoothInterface),
    init,
    enable,
    disable,
    cleanup,
    get_adapter_properties,
    get_adapter_property,
    set_adapter_property,
    get_remote_device_properties,
    get_remote_device_property,
    set_remote_device_property,
    get_remote_service_record,
    get_remote_services,
    start_discovery,
    cancel_discovery,
    create_bond,
    create_bond_out_of_band,
    remove_bond,
    cancel_bond,
    get_connection_state,
    pin_reply,
    ssp_reply,
    get_profile_interface,
    dut_mode_configure,
    dut_mode_send,
#if BLE_INCLUDED == TRUE
    le_test_mode,
#else
    NULL,
#endif
    config_hci_snoop_log,
    set_os_callouts,
    read_energy_info,
    dump,
    config_clear,
    interop_database_clear,
    interop_database_add,
};
#endif
const bt_interface_t* bluetooth__get_bluetooth_interface ()
{
    /* fixme -- add property to disable bt interface ? */

    return &bluetoothInterface;
}

static int close_bluetooth_stack(struct hw_device_t* device)
{
    UNUSED(device);
    cleanup();
    return 0;
}

static int open_bluetooth_stack(const struct hw_module_t *module, UNUSED_ATTR char const *name, struct hw_device_t **abstraction) {
  static bluetooth_device_t device = {
    .common = {
      .tag = HARDWARE_DEVICE_TAG,
      .version = 0,
      .close = close_bluetooth_stack,
    },
    .get_bluetooth_interface = bluetooth__get_bluetooth_interface
  };

  device.common.module = (struct hw_module_t *)module;
  *abstraction = (struct hw_device_t *)&device;
  return 0;
}

static struct hw_module_methods_t bt_stack_module_methods = {
    .open = open_bluetooth_stack,
};

EXPORT_SYMBOL struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = BT_HARDWARE_RTK_MODULE_ID,
    .name = "Bluetooth Stack",
    .author = "The Android Open Source Project",
    .methods = &bt_stack_module_methods
};
