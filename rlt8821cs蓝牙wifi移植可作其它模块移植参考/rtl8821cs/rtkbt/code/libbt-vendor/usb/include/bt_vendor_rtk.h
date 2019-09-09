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

/******************************************************************************
 *
 *  Filename:      bt_vendor_rtk.h
 *
 *  Description:   A wrapper header file of bt_vendor_lib.h
 *
 *                 Contains definitions specific for interfacing with Broadcom
 *                 Bluetooth chipsets
 *
 ******************************************************************************/

#ifndef BT_VENDOR_RTK_H
#define BT_VENDOR_RTK_H

#include "bt_vendor_lib.h"
#include "vnd_buildcfg.h"
#include <string.h>

/******************************************************************************
**  Constants & Macros
******************************************************************************/

#ifndef FALSE
#define FALSE  0
#endif

#ifndef TRUE
#define TRUE   (!FALSE)
#endif

/* Device port name where Bluetooth controller attached */
#ifndef BLUETOOTH_UART_DEVICE_PORT
#define BLUETOOTH_UART_DEVICE_PORT      "/dev/ttyO1"    /* maguro */
#endif

/******************************************************************************
**  Extern variables and functions
******************************************************************************/
void userial_vendor_init(char *bt_device_node);
int userial_vendor_open(void);
void userial_vendor_close(void);

extern bt_vendor_callbacks_t *bt_vendor_cbacks;

#endif /* BT_VENDOR_RTK_H */

