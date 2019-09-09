/******************************************************************************
 *
 *  Copyright (C) 2015 Google, Inc.
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

#pragma once

#include <stdbool.h>

#include "btcore/include/bdaddr.h"

static const char INTEROP_MODULE[] = "interop_module";

// NOTE:
// Only add values at the end of this enum and do NOT delete values
// as they may be used in dynamic device configuration.
typedef enum {
  // Disable secure connections
  // This is for pre BT 4.1/2 devices that do not handle secure mode
  // very well.
  INTEROP_DISABLE_LE_SECURE_CONNECTIONS = 0,

  // Some devices have proven problematic during the pairing process, often
  // requiring multiple retries to complete pairing. To avoid degrading the user
  // experience for those devices, automatically re-try pairing if page
  // timeouts are received during pairing.
  INTEROP_AUTO_RETRY_PAIRING,

  // Devices requiring this workaround do not handle Bluetooth Absolute Volume
  // control correctly, leading to undesirable (potentially harmful) volume levels
  // or general lack of controlability.
  INTEROP_DISABLE_ABSOLUTE_VOLUME,

  // Disable automatic pairing with headsets/car-kits
  // Some car kits do not react kindly to a failed pairing attempt and
  // do not allow immediate re-pairing. Blacklist these so that the initial
  // pairing attempt makes it to the user instead.
  INTEROP_DISABLE_AUTO_PAIRING,

  // Use a fixed pin for specific keyboards
  // Keyboards should use a variable pin at all times. However, some keyboards
  // require a fixed pin of all 0000. This workaround enables auto pairing for
  // those keyboards.
  INTEROP_KEYBOARD_REQUIRES_FIXED_PIN,

  // Some headsets have audio jitter issues because of increased re-transmissions as the
  // 3 Mbps packets have a lower link margin, and are more prone to interference. We can
  // disable 3DH packets (use only 2DH packets) for the ACL link to improve sensitivity
  // when streaming A2DP audio to the headset. Air sniffer logs show reduced
  // re-transmissions after switching to 2DH packets.
  //
  // Disable 3Mbps packets and use only 2Mbps packets for ACL links when streaming audio.
  INTEROP_2MBPS_LINK_ONLY
} interop_feature_t;

// Check if a given |addr| matches a known interoperability workaround as identified
// by the |interop_feature_t| enum. This API is used for simple address based lookups
// where more information is not available. No look-ups or random address resolution
// are performed on |addr|.
bool interop_match_addr(const interop_feature_t feature, const bt_bdaddr_t *addr);

// Check if a given remote device |name| matches a known interoperability workaround.
// Name comparisons are case sensitive and do not allow for partial matches. As in, if
// |name| is "TEST" and a workaround exists for "TESTING", then this function will
// return false. But, if |name| is "TESTING" and a workaround exists for "TEST", this
// function will return true.
// |name| cannot be null and must be null terminated.
bool interop_match_name(const interop_feature_t feature, const char *name);

// Add a dynamic interop database entry for a device matching the first |length| bytes
// of |addr|, implementing the workaround identified by |feature|. |addr| may not be
// null and |length| must be greater than 0 and less than sizeof(bt_bdaddr_t).
// As |interop_feature_t| is not exposed in the public API, feature must be a valid
// integer representing an optoin in the enum.
void interop_database_add(const uint16_t feature, const bt_bdaddr_t *addr, size_t length);

// Clear the dynamic portion of the interoperability workaround database.
void interop_database_clear(void);
