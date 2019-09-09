/******************************************************************************
 *
 *  Copyright (C) 2016 Realtek Corporation.
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
*	Module Name:
*	    rtk_parse.h
*
*	Abstract:
*	    Contains wifi-bt coex functions implemented by bluedroid stack
*
*	Major Change History:
*	      When             Who       What
*	    ---------------------------------------------------------------
*	    2015-12-15      lamparten   modified
*	    2014-10-23       kyle_xu    modified
*
*	Notes:
*         This is designed for wifi-bt Coex in Android 6.0.
*
******************************************************************************/


#ifndef RTK_PARSE_H
#define RTK_PARSE_H

#pragma once

#include <stdlib.h>
#include "hci_layer.h"
#include "bt_types.h"
#include "buffer_allocator.h"
#include <string.h>
#include <string.h>
#include <strings.h>
/******************************************************************************
**  Constants & Macros
******************************************************************************/
#define HOST_PROFILE_INFO

/******************************************************************************
**  Type definitions
******************************************************************************/
typedef unsigned char   UINT8;
#define BD_ADDR_LEN     6                   /* Device address length */
typedef UINT8 BD_ADDR[BD_ADDR_LEN];         /* Device address */
typedef void* TRANSAC;


/******************************************************************************
**  Extern variables and functions
******************************************************************************/
extern uint8_t coex_log_enable;

/******************************************************************************
**  Functions
******************************************************************************/
typedef struct rtk_parse_manager_t {

    void (*rtk_parse_internal_event_intercept)(uint8_t *p);

    void (*rtk_parse_l2cap_data)(uint8_t *p, uint8_t direction);

    void (*rtk_parse_init)(hci_t *hci_if);

    void (*rtk_parse_cleanup)();

    void (*rtk_parse_command)(uint8_t *p);

    void (*rtk_add_le_profile)(BD_ADDR bdaddr, uint16_t handle, uint8_t profile_map);

    void (*rtk_delete_le_profile)(BD_ADDR bdaddr, uint16_t handle, uint8_t profile_map);

    void (*rtk_add_le_data_count)(uint8_t data_type);

    void (*rtk_add_bitpool_to_fw)(uint8_t bitpool);

}rtk_parse_manager_t;

const rtk_parse_manager_t *rtk_parse_manager_get_interface();

#endif /*RTK_PARSE_H*/
