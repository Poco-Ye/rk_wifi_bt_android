LOCAL_PATH := $(call my-dir)
# Common macros inherited by sub-makefiles
rtk_local_C_INCLUDES := \
        $(LOCAL_PATH)/include \
        $(LOCAL_PATH)/.. \
        $(LOCAL_PATH)/../bta/hh \
        $(LOCAL_PATH)/../bta/include \
        $(LOCAL_PATH)/../bta/sys \
        $(LOCAL_PATH)/../bta/dm \
        $(LOCAL_PATH)/../include \
        $(LOCAL_PATH)/../stack/include \
        $(LOCAL_PATH)/../stack/l2cap \
        $(LOCAL_PATH)/../stack/a2dp \
        $(LOCAL_PATH)/../stack/btm \
        $(LOCAL_PATH)/../stack/avdt \
        $(LOCAL_PATH)/../hcis \
        $(LOCAL_PATH)/../hcis/include \
        $(LOCAL_PATH)/../hcis/patchram \
        $(LOCAL_PATH)/../udrv/include \
        $(LOCAL_PATH)/../btif/include \
        $(LOCAL_PATH)/../btif/co \
        $(LOCAL_PATH)/../hci/include\
        $(LOCAL_PATH)/../brcm/include \
        $(LOCAL_PATH)/../embdrv/sbc/encoder/include \
        $(LOCAL_PATH)/../utils/include \
        $(LOCAL_PATH)/../osi/include \
        external/tinyxml2 \
        $(bluetooth_C_INCLUDES)

rtk_local_CFLAGS += -DBUILDCFG $(bluetooth_CFLAGS)

include $(call all-subdir-makefiles)
