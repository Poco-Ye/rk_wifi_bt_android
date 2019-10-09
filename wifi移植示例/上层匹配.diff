+++hardware/libhardware_legacy/wifi/rk_wifi_ctrl.c

int check_wifi_chip_type_string(char *type)
{
	if (identify_sucess == -1) {
		if (get_wifi_device_id(SDIO_DIR, PREFIX_SDIO) == 0)
			ALOGD("SDIO WIFI identify sucess");
		else if (get_wifi_device_id(USB_DIR, PREFIX_USB) == 0)
			ALOGD("USB WIFI identify sucess");
		else if (get_wifi_device_id(PCIE_DIR, PREFIX_PCIE) == 0)
			ALOGD("PCIE WIFI identify sucess");
		else {
			ALOGD("maybe there is no usb wifi or sdio or pcie wifi,set default wifi module Brocom APXXX");
			strcpy(recoginze_wifi_chip, "APXXX");
			identify_sucess = 1 ;
		}
	}

	strcpy(type, recoginze_wifi_chip);
	ALOGD("%s: %s", __func__, type);
	return 0;
}



+++hardware/libhardware_legacy/wifi/wifi.c

int wifi_load_driver()
{
	char* wifi_ko_path = NULL ;
	char* wifi_ko_arg =NULL;
	int i = 0;
	char driver_status[PROPERTY_VALUE_MAX];
	int count = 100; /* wait at most 20 seconds for completion */
	if (wifi_dirver_is_loaded == 1) {
		return 0;
	}
	if (check_wireless_ready()) {
		wifi_dirver_is_loaded = 1;
		return 0;
	}
	ALOGD("%s", __func__);
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
	if (wifi_ko_path == NULL) {
		ALOGE("%s falied to find wifi driver for type=%s", __func__, wifi_type);
		return -1;
	}

	if (insmod(wifi_ko_path, wifi_ko_arg) < 0) {
		ALOGE("%s insmod %s failed", __func__, wifi_ko_path);
		return -1;
	}
	if (strcmp(FIRMWARE_LOADER,"") == 0) {
        /* usleep(WIFI_DRIVER_LOADER_DELAY); */
		property_set(DRIVER_PROP_NAME, "ok");
	}
	else {
		property_set("ctl.start", FIRMWARE_LOADER);
	}
	sched_yield();
	while (count-- > 0) {
	/*
        	if (property_get(DRIVER_PROP_NAME, driver_status, NULL)) {
        	if (strcmp(driver_status, "ok") == 0)
        	return 0;
        	else if (strcmp(DRIVER_PROP_NAME, "failed") == 0) {
        	wifi_unload_driver();
        	return -1;
        	}
        }
        */
	if (check_wireless_ready()) {
		property_set(DRIVER_PROP_NAME, "ok");
		return 0;
        }
        usleep(200000);
	}
	property_set(DRIVER_PROP_NAME, "timeout");
	wifi_unload_driver();
	return -1;
}
