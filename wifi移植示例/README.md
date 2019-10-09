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

      
