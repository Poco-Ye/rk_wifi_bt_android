# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := audio.primary.$(TARGET_BOARD_HARDWARE)
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_SRC_FILES := \
        audio_setting.c \
	audio_bitstream.c \
	audio_hw.c \
	alsa_route.c \
	alsa_mixer.c \
	voice_preprocess.c \
	audio_hw_hdmi.c
LOCAL_C_INCLUDES += \
	external/tinyalsa/include \
	$(call include-path-for, audio-utils) \
	$(call include-path-for, audio-route) \
	$(call include-path-for, speex)


LOCAL_HEADER_LIBRARIES += libhardware_headers
LOCAL_CFLAGS := -Wno-unused-parameter
LOCAL_CFLAGS += -DLIBTINYALSA_ENABLE_VNDK_EXT
ifneq ($(filter box atv, $(strip $(TARGET_BOARD_PLATFORM_PRODUCT))), )
LOCAL_CFLAGS += -DBOX_HAL
endif
ifeq ($(strip $(BOARD_USE_DRM)),true)
LOCAL_CFLAGS += -DUSE_DRM
endif
ifeq ($(strip $(BOARD_USE_AUDIO_3A)),true)
LOCAL_CFLAGS += -DAUDIO_3A
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3368)
LOCAL_CFLAGS += -DRK3368
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3228h)
        LOCAL_CFLAGS += -DRK3228
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3328)
        LOCAL_CFLAGS += -DRK3228
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3228)
        LOCAL_CFLAGS += -DRK3228
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk322x)
	LOCAL_CFLAGS += -DRK3228
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3128h)
        LOCAL_CFLAGS += -DRK3228
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3399)
    LOCAL_CFLAGS += -DRK3399
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3399pro)
    LOCAL_CFLAGS += -DRK3399
endif
ifeq ($(strip $(TARGET_BOARD_PLATFORM)),rk3128)
    LOCAL_CFLAGS += -DRK3128
endif

LOCAL_CFLAGS += -DRK3399_LAPTOP
LOCAL_CFLAGS += -DBT_AP_SCO

ifeq ($(AUD_VOICE_CONFIG),voice_support)
LOCAL_CFLAGS += -DVOICE_SUPPORT
endif
LOCAL_CFLAGS += -Wno-error
LOCAL_SHARED_LIBRARIES := liblog libcutils libtinyalsa libaudioutils libaudioroute libhardware_legacy libspeexresampler
LOCAL_STATIC_LIBRARIES := libspeex
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -Wno-error
LOCAL_SRC_FILES:= amix.c alsa_mixer.c
LOCAL_MODULE:= amix
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SHARED_LIBRARIES := liblog libc libcutils
LOCAL_MODULE_TAGS:= debug
include $(BUILD_EXECUTABLE)
