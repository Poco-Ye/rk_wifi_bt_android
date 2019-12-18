```
1、首先强调wifi驱动只要编译了就可以了，就是一个目录，在config很好加载

2、cat /sys/class/rkwifi/chip 这个是dts的wifi 设置，没有会造成wifi不运行，在驱动头部被返回或者博通的驱动不知道下载哪个patch

3、pid vid没有支持，比如很多usb的wifi驱动，然后读到的pid vid 不在驱动的列表里面，那就是不支持，还有如果是sdio wifi的驱动，
那就可以在上层添加vid pid，这样在加载对应得驱动 


12-16 17:58:02.331 D/WifiHW  ( 2305): uevent path:/sys/bus/sdio/devices/../uevent
12-16 17:58:02.331 D/WifiHW  ( 2305): wifi detectd return ret:-1
12-16 17:58:02.331 D/WifiHW  ( 2305): uevent path:/sys/bus/usb/devices/./uevent
12-16 17:58:02.331 D/WifiHW  ( 2305): uevent path:/sys/bus/usb/devices/../uevent
12-16 17:58:02.331 D/WifiHW  ( 2305): uevent path:/sys/bus/usb/devices/1-1/uevent

hardware/libhardware_legacy/wifi/rk_wifi_ctrl.c

static wifi_device supported_wifi_devices[] = {
	{"RTL8188EU",	"0bda:8179"},
	{"RTL8188EU",	"0bda:0179"},
	{"RTL8723BU",	"0bda:b720"},
	{"RTL8723BS",	"024c:b723"},
	{"RTL8822BS",	"024c:b822"},
	{"RTL8723CS",	"024c:b703"},
	{"RTL8723DS",	"024c:d723"},
	{"RTL8188FU",	"0bda:f179"},
	{"RTL8822BU",	"0bda:b82c"},
	{"RTL8189ES",	"024c:8179"},
	{"RTL8189FS",	"024c:f179"},
	{"RTL8192DU",	"0bda:8194"},
	{"RTL8812AU",	"0bda:8812"},
	{"SSV6051",	"3030:3030"},
	{"ESP8089",	"6666:1111"},
	{"AP6354",	"02d0:4354"},
	{"AP6330",	"02d0:4330"},
	{"AP6356S",	"02d0:4356"},
	{"AP6335",	"02d0:4335"},
	{"AP6255",      "02d0:a9bf"},
	{"RTL8822BE",	"10ec:b822"},
};


driver/wireless/rockchip_wlan/rtl8723au/os_dep/linux/usb_intf.c

	/****** 8188CUS Dongle ********/ \
	{USB_DEVICE(0x2019, 0xED17)},/* PCI - Edimax */ \
	{USB_DEVICE(0x0DF6, 0x0052)},/* Sitecom - Edimax */ \
	{USB_DEVICE(0x7392, 0x7811)},/* Edimax - Edimax */ \
	{USB_DEVICE(0x07B8, 0x8189)},/* Abocom - Abocom */ \
	{USB_DEVICE(0x0EB0, 0x9071)},/* NO Brand - Etop */ \
	{USB_DEVICE(0x06F8, 0xE033)},/* Hercules - Edimax */ \
	{USB_DEVICE(0x103C, 0x1629)},/* HP - Lite-On ,8188CUS Slim Combo */ \
	{USB_DEVICE(0x2001, 0x3308)},/* D-Link - Alpha */ \
	{USB_DEVICE(0x050D, 0x1102)},/* Belkin - Edimax */ \
	{USB_DEVICE(0x2019, 0xAB2A)},/* Planex - Abocom */ \
	{USB_DEVICE(0x20F4, 0x648B)},/* TRENDnet - Cameo */ \
	{USB_DEVICE(0x4855, 0x0090)},/*  - Feixun */ \
	{USB_DEVICE(0x13D3, 0x3357)},/*  - AzureWave */ \
	{USB_DEVICE(0x0DF6, 0x005C)},/* Sitecom - Edimax */ \
	{USB_DEVICE(0x0BDA, 0x5088)},/* Thinkware - CC&C */ \
	{USB_DEVICE(0x4856, 0x0091)},/* NetweeN - Feixun */ \
	{USB_DEVICE(0x0846, 0x9041)}, /* Netgear - Cameo */ \
	{USB_DEVICE(0x2019, 0x4902)},/* Planex - Etop */ \
	{USB_DEVICE(0x2019, 0xAB2E)},/* SW-WF02-AD15 -Abocom */ \
	{USB_DEVICE(0x2001, 0x330B)}, /* D-LINK - T&W */ \
	{USB_DEVICE(0xCDAB, 0x8010)}, /* - - compare */ \
	{USB_DEVICE(0x0B05, 0x17BA)}, /* ASUS - Edimax */ \
	{USB_DEVICE(0x0BDA, 0x1E1E)}, /* Intel - - */ \

```




博通下层匹配主要就是根据DTS上的chip_type下不同的patch，rtk直接跑不同的驱动就可以了
```
driver/rfkill/rfkill-wlan.c
of_property_read_string(node, "wifi_chip_type", &strings);

--- a/drivers/net/wireless/rockchip_wlan/rkwifi/rk_wifi_config.c
+++ b/drivers/net/wireless/rockchip_wlan/rkwifi/rk_wifi_config.c
@@ -67,6 +72,11 @@ if (chip == WIFI_AP6335) {
 	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6335.txt");
 }
 
+if (chip == WIFI_AP6354) {
+    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm4354a1_ag.bin");
+        sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_ap6354.txt");
+}
+

```




博通和rtk上层匹配主要就是根据pid vid的chip_type加载不同的.ko就是相应模块的wifi驱动

```
hardware/libhardware_legacy/wifi/rk_wifi_ctrl.c

int check_wifi_chip_type_string(char *type)
{
	if (identify_sucess == -1) {
		if (get_wifi_device_id(SDIO_DIR, PREFIX_SDIO) == 0)
			ALOGD("SDIO WIFI identify sucess");
		else if (get_wifi_device_id(USB_DIR, PREFIX_USB) == 0)
			ALOGD("USB WIFI identify sucess");
		else if (get_wifi_device_id(PCIE_DIR, PREFIX_PCIE) == 0)
			ALOGD("PCIE WIFI identify sucess");
      
      
hardware/libhardware_legacy/wifi/wifi.c

int wifi_load_driver()

	if (wifi_type[0] == 0) {
		check_wifi_chip_type_string(wifi_type);
		save_wifi_chip_type(wifi_type);
	}
	for (i=0; i< (int)(sizeof(module_list) / sizeof(module_list[0])); i++) {
		if (!strcmp(wifi_type , module_list[i].wifi_name)) {
			wifi_ko_path = module_list[i].wifi_module_path;
			wifi_ko_arg = module_list[i].wifi_module_arg;
			ALOGD("%s matched ko file path  %s", __func__, wifi_ko_path);
			break;
		}
	}
  


```

      
