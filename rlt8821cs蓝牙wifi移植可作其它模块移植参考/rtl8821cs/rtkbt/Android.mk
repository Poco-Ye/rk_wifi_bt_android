ifeq ($(BOARD_HAVE_BLUETOOTH_RTK),true)
LOCAL_PATH := $(call my-dir)
include $(call all-makefiles-under,$(LOCAL_PATH))
endif