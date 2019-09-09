# RELEASE NAME: 20181224_BT_ANDROID_7.0

BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_RTK := true
BOARD_HAVE_BLUETOOTH_RTK_COEX := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)/bluetooth

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/system/etc/bluetooth/rtkbt.conf:system/etc/bluetooth/rtkbt.conf \
	$(LOCAL_PATH)/system/etc/firmware/rtl8703as_config:system/etc/firmware/rtl8703as_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8703as_fw:system/etc/firmware/rtl8703as_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8703bs_config:system/etc/firmware/rtl8703bs_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8703bs_fw:system/etc/firmware/rtl8703bs_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8703cs_config:system/etc/firmware/rtl8703cs_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8703cs_fw:system/etc/firmware/rtl8703cs_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723a_config:system/etc/firmware/rtl8723a_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723a_fw:system/etc/firmware/rtl8723a_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723as_config:system/etc/firmware/rtl8723as_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723as_fw:system/etc/firmware/rtl8723as_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723b_config:system/etc/firmware/rtl8723b_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723b_fw:system/etc/firmware/rtl8723b_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723bs_config:system/etc/firmware/rtl8723bs_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723bs_fw:system/etc/firmware/rtl8723bs_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723bs_VQ0_config:system/etc/firmware/rtl8723bs_VQ0_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723bs_VQ0_fw:system/etc/firmware/rtl8723bs_VQ0_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723bu_config:system/etc/firmware/rtl8723bu_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723c_fw:system/etc/firmware/rtl8723c_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723cs_cg_config:system/etc/firmware/rtl8723cs_cg_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723cs_cg_fw:system/etc/firmware/rtl8723cs_cg_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723cs_vf_config:system/etc/firmware/rtl8723cs_vf_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723cs_vf_fw:system/etc/firmware/rtl8723cs_vf_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723cs_xx_config:system/etc/firmware/rtl8723cs_xx_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723cs_xx_fw:system/etc/firmware/rtl8723cs_xx_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723d_config:system/etc/firmware/rtl8723d_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723d_fw:system/etc/firmware/rtl8723d_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723ds_config:system/etc/firmware/rtl8723ds_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8723ds_fw:system/etc/firmware/rtl8723ds_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761a_config:system/etc/firmware/rtl8761a_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761at_config:system/etc/firmware/rtl8761at_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761at_fw:system/etc/firmware/rtl8761at_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761au8192ee_fw:system/etc/firmware/rtl8761au8192ee_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761au8812ae_fw:system/etc/firmware/rtl8761au8812ae_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761au_fw:system/etc/firmware/rtl8761au_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761aw8192eu_config:system/etc/firmware/rtl8761aw8192eu_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8761aw8192eu_fw:system/etc/firmware/rtl8761aw8192eu_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821a_config:system/etc/firmware/rtl8821a_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821a_fw:system/etc/firmware/rtl8821a_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821as_config:system/etc/firmware/rtl8821as_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821as_fw:system/etc/firmware/rtl8821as_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821c_config:system/etc/firmware/rtl8821c_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821c_fw:system/etc/firmware/rtl8821c_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821cs_config:system/etc/firmware/rtl8821cs_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8821cs_fw:system/etc/firmware/rtl8821cs_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8822b_config:system/etc/firmware/rtl8822b_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8822b_fw:system/etc/firmware/rtl8822b_fw \
	$(LOCAL_PATH)/system/etc/firmware/rtl8822bs_config:system/etc/firmware/rtl8822bs_config \
	$(LOCAL_PATH)/system/etc/firmware/rtl8822bs_fw:system/etc/firmware/rtl8822bs_fw \
	$(LOCAL_PATH)/system/etc/permissions/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
	$(LOCAL_PATH)/system/etc/permissions/android.hardware.bluetooth.xml:system/etc/permissions/android.hardware.bluetooth.xml \


PRODUCT_PACKAGES += \
	Bluetooth \
	audio.a2dp.default
