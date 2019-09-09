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

#include "hci_hal.h"
#ifdef BLUETOOTH_RTK
extern bool bluetooth_rtk_h5_flag;
#endif
const hci_hal_t *hci_hal_get_interface() {
#if HCI_USE_MCT
  return hci_hal_mct_get_interface();
#else
#ifdef BLUETOOTH_RTK
  if(bluetooth_rtk_h5_flag) {
    return hci_hal_h5_get_interface();
  }
  else
    return hci_hal_h4_get_interface();
#else
  return hci_hal_h4_get_interface();
#endif
#endif
}

