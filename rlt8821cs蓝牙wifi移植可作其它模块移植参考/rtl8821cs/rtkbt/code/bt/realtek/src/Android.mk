LOCAL_PATH := $(call my-dir)

# libbt-rtkbt.a
include $(CLEAR_VARS)

LOCAL_SRC_FILES += rtkbt_api.c rtkbt_conf.c

LOCAL_C_INCLUDES := $(rtk_local_C_INCLUDES)
LOCAL_CFLAGS += $(rtk_local_CFLAGS) -Wno-error=unused-parameter

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libc
LOCAL_MODULE := libbt-rtkbt
#LOCAL_MULTILIB := 32

include $(BUILD_STATIC_LIBRARY)

