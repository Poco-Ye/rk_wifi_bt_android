一、WIFI驱动移植说明
1、驱动丢到下面目录 drivers/net/wireless/rockchip_wlan


2、增加Makefile
lspei@ubuntu:~/work/3229/rk3229_android7.1_box_v1.00_20170831/kernel/drivers/net/wireless$ git diff .
diff --git a/drivers/net/wireless/Kconfig b/drivers/net/wireless/Kconfig
index a861d98..6232174 100644
--- a/drivers/net/wireless/Kconfig
+++ b/drivers/net/wireless/Kconfig
@ -58,6 +58,7 @ source "drivers/net/wireless/rockchip_wlan/rtl8189fs/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rtl8188fu/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rtl8822bs/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rtl8822bu/Kconfig" 
+source "drivers/net/wireless/rockchip_wlan/rtl8821cs/Kconfig"



lspei@ubuntu:~/work/3229/rk3229_android7.1_box_v1.00_20170831/kernel/drivers/net/wireless$ git diff Kconfig
diff --git a/drivers/net/wireless/Kconfig b/drivers/net/wireless/Kconfig
index a861d98..6232174 100644
--- a/drivers/net/wireless/Kconfig
+++ b/drivers/net/wireless/Kconfig
@ -58,6 +58,7 @ source "drivers/net/wireless/rockchip_wlan/rtl8189fs/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rtl8188fu/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rtl8822bs/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rtl8822bu/Kconfig" 
+source "drivers/net/wireless/rockchip_wlan/rtl8821cs/Kconfig" 
endif
source "drivers/net/wireless/rockchip_wlan/esp8089/Kconfig" 
source "drivers/net/wireless/rockchip_wlan/rkwifi/Kconfig"

二、蓝牙驱动移植说明

1、对于android 4.4 5.1 6.0 直接替换固件
vendor/rockchip/common/bluetooth/realtek/firmware/uart/
可能旧的libvendor吃不到对应固件，可用libbt-vendor进行替换，若可以吃到固件测不需替换

2、7.1 可以直接替换hardware/realtek/rtkbt

