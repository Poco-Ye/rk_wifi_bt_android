/******************************************************************************
 *
 *  Copyright (C) 2013 Google, Inc.
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

#define LOG_TAG "rtk_btsnoop_net"

#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#include "osi/include/osi.h"
#include "osi/include/log.h"
#include "hci_hal.h"

#define DATA_DIRECT_2_ELLISY 1

#define HCI_COMMAND         0x01
#define HCI_ACL_DATA_H2C    0x02
#define HCI_ACL_DATA_C2H    0x82
#define HCI_SCO_DATA_H2C    0x03
#define HCI_SCO_DATA_C2H    0x83
#define HCI_EVENT           0x84

#define HCI_COMMAND_PKT         0x01
#define HCI_ACLDATA_PKT         0x02
#define HCI_SCODATA_PKT         0x03
#define HCI_EVENT_PKT           0x04


extern unsigned int rtkbt_logfilter;

static void rtk_safe_close_(int *fd);
static void *rtk_listen_fn_(void *context);

static const char *RTK_LISTEN_THREAD_NAME_ = "rtk_btsnoop_net";
static const int RTK_LOCALHOST_ = 0xC0A80AE2;       // 192.168.10.226
static const int RTK_LISTEN_PORT_ = 8872;

static const int RTK_REMOTEHOST_ = 0xC0A80A03;       // 192.168.10.21
static const int RTK_REMOTE_PORT_ = 24352;


static pthread_t rtk_listen_thread_;
static bool rtk_listen_thread_valid_ = false;
static pthread_mutex_t rtk_client_socket_lock_ = PTHREAD_MUTEX_INITIALIZER;
static int rtk_listen_socket_ = -1;

void rtk_btsnoop_net_open() {
    rtk_listen_thread_valid_ = (pthread_create(&rtk_listen_thread_, NULL, rtk_listen_fn_, NULL) == 0);
    if (!rtk_listen_thread_valid_) {
        LOG_ERROR(LOG_TAG, "%s pthread_create failed: %s", __func__, strerror(errno));
    } else {
        LOG_DEBUG(LOG_TAG, "initialized");
    }
}

void rtk_btsnoop_net_close() {
    if (rtk_listen_thread_valid_) {
        shutdown(rtk_listen_socket_, SHUT_RDWR);
        pthread_join(rtk_listen_thread_, NULL);
        rtk_listen_thread_valid_ = false;
    }
}

void rtk_btsnoop_net_write(serial_data_type_t type, uint8_t *data, bool is_received) {
    if (rtk_listen_socket_ == -1) {
        return;
    }
    int length = 0;
    uint8_t *p = data;

    switch (type) {
    case HCI_COMMAND_PKT:
        if(((rtkbt_logfilter & 1) == 0) || (*p != 0x94) || (*(p + 1) != 0xfc))
            length = data[2] + 3;
        else
            return;
    break;
    case HCI_ACLDATA_PKT:
        length = (data[3] << 8) + data[2] + 4;
    break;
    case HCI_SCODATA_PKT:
        length = data[2] + 3;
    break;
    case HCI_EVENT_PKT:
    if((*(p + 3) == 0x94) && (*(p + 4) == 0xfc) && (*(p + 5) == 0x00)&&(rtkbt_logfilter&1)){return;}
    else
        length = data[1] + 2;
    break;
    default:
        break;
    }


    uint8_t buffer[4126] = {0};
    //uint8_t test_buffer[] = {0x03, 0x00, 0x00, 0x00, 0x01, 0x01, 0x10, 0x00};
    //uint8_t test_buffer2[] = {0x01, 0x10, 0x00};
    struct sockaddr_in client_addr;
    int i = 0;

#if DATA_DIRECT_2_ELLISY
    uint8_t bit_rate[4] = {0x00, 0x1b, 0x37, 0x4b};
    struct tm *t;
    time_t tt;
    time(&tt);
    t = localtime(&tt);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t nano_time = (t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec) * 1000 * 1000LL * 1000 + tv.tv_usec * 1000;
    uint16_t year = (t->tm_year + 1900) & 0xFFFF;
    uint8_t  month = (t->tm_mon+1) & 0xFF;
    uint8_t  day =
    buffer[0] = 0x02;
    buffer[1] = 0x00;
    buffer[2] = 0x01;
    buffer[3] = 0x02;
    //time
    memcpy(&buffer[4], &year, 2);
    buffer[6] = month;
    buffer[7] = day;
    memcpy(&buffer[8], &nano_time, 6);
    //bit rate
    buffer[14] = 0x80;
    memcpy(&buffer[15], bit_rate, 4);
    //type
    buffer[19] = 0x81;
    i = 20;
#else
    memcpy(&buffer[i], &length, sizeof(int));
    i = 4;
#endif
    switch (type) {
        case HCI_COMMAND_PKT:
        buffer[i] = HCI_COMMAND;
        break;

        case HCI_ACLDATA_PKT:
        if(is_received) {
            buffer[i] = HCI_ACL_DATA_C2H;
        }
        else {
            buffer[i] = HCI_ACL_DATA_H2C;
        }
        break;

        case HCI_SCODATA_PKT:
        if(is_received) {
            buffer[i] = HCI_SCO_DATA_C2H;
        }
        else {
            buffer[i] = HCI_SCO_DATA_H2C;
        }
        break;

        case HCI_EVENT_PKT:
        buffer[i] = HCI_EVENT;
        break;

        default:
        buffer[i] = 0;
        break;

    }
#if DATA_DIRECT_2_ELLISY
    //buffer[i] = HCI_COMMAND;
    buffer[21] = 0x82;
    i = 22;
#else
    i = 5;
#endif
    memcpy(&buffer[i], data, length);
    //memcpy(&buffer[i], test_buffer2, 3);
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(RTK_REMOTEHOST_);
    client_addr.sin_port = htons(RTK_REMOTE_PORT_);
    pthread_mutex_lock(&rtk_client_socket_lock_);
    sendto(rtk_listen_socket_, buffer, (length+i), 0,(struct sockaddr*)&client_addr, sizeof(struct sockaddr_in));
    //sendto(rtk_listen_socket_, buffer, 25, 0,(struct sockaddr*)&client_addr, sizeof(struct sockaddr_in));
    pthread_mutex_unlock(&rtk_client_socket_lock_);
}

static void *rtk_listen_fn_(UNUSED_ATTR void *context) {
    prctl(PR_SET_NAME, (unsigned long)RTK_LISTEN_THREAD_NAME_, 0, 0, 0);

    rtk_listen_socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (rtk_listen_socket_ == -1) {
        LOG_ERROR(LOG_TAG, "%s socket creation failed: %s", __func__, strerror(errno));
        goto cleanup;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(RTK_LOCALHOST_);
    addr.sin_port = htons(RTK_LISTEN_PORT_);

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(RTK_REMOTEHOST_);
    client_addr.sin_port = htons(RTK_REMOTE_PORT_);

    if (bind(rtk_listen_socket_, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        LOG_ERROR(LOG_TAG, "%s unable to bind listen socket: %s", __func__, strerror(errno));
        goto cleanup;
    }

    return NULL;
cleanup:
    rtk_safe_close_(&rtk_listen_socket_);
    return NULL;
}

static void rtk_safe_close_(int *fd) {
  assert(fd != NULL);
  if (*fd != -1) {
    close(*fd);
    *fd = -1;
  }
}
