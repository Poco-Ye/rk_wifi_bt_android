```
sdk_project@aaaaa:~/7.1_sdk/RK3368H_RK3368_Android7.1_SDK_20170401/packages/apps/Bluetooth$ git diff .
diff --git a/jni/com_android_bluetooth_btservice_AdapterService.cpp b/jni/com_android_bluetooth_btservice_AdapterService.cpp
index cff38a4..347370d 100755
--- a/jni/com_android_bluetooth_btservice_AdapterService.cpp
+++ b/jni/com_android_bluetooth_btservice_AdapterService.cpp
@@ -689,7 +689,8 @@ static void classInitNative(JNIEnv* env, jclass clazz) {
     const char *id = (strcmp(value, "1")? BT_STACK_MODULE_ID : BT_STACK_TEST_MODULE_ID);
 
     char type[64];
-    check_wifi_chip_type_string(type);
+    //check_wifi_chip_type_string(type);
+    strcmp(type，"RTL8723BU");
     if (!strncmp(type, "RTL", 3)) {
         ALOGD("%s, load %s.default.so", __func__, BT_STACK_RTK_MODULE_ID);
         err = hw_get_module(BT_STACK_RTK_MODULE_ID, (hw_module_t const**)&module);
sdk_project@aaaaa:~/7.1_sdk/RK3368H_RK3368_Android7.1_SDK_20170401/packages/apps/Bluetooth

sdk_project@aaaaa:~/7.1_sdk/RK3368H_RK3368_Android7.1_SDK_20170401/hardware/realtek/rtkbt/code/bt$ git diff .
diff --git a/rtkbt/code/bt/main/bte_conf.c b/rtkbt/code/bt/main/bte_conf.c
index 704fd4c..10644cd 100755
--- a/rtkbt/code/bt/main/bte_conf.c
+++ b/rtkbt/code/bt/main/bte_conf.c
@@ -52,6 +52,7 @@ void bte_load_rtkbt_conf(const char *path)
     strlcpy(bt_hci_device_node, config_get_string(config, CONFIG_DEFAULT_SECTION, "BtDeviceNode","/dev/rtk_btusb"), sizeof(bt_hci_device_node));
 #else
     check_wifi_chip_type_string(type);
+    strcmp(type,"RTL8723BU");
     if (strstr(type, "AU")!=NULL || strstr(type, "BU")!=NULL || strstr(type, "RTL8822BE") != NULL) {
         strlcpy(bt_hci_device_node, "/dev/rtk_btusb", sizeof(bt_hci_device_node));
     } else if (!strncmp(type, "RTL", 3)) {
sdk_project@aaaaa:~/7.1_sdk/RK3368H_RK3368_Android7.1_SDK_20170401/hardware/realtek/rtkbt/code/bt$ 

packages\apps\Bluetooth\res\values\config.xml
-<bool name="profile_supported_rtkbt">false</bool>
+<bool name="profile_supported_rtkbt">true</bool>

```
```
diff --git a/libwifi_hal/rk_wifi_ctrl.cpp b/libwifi_hal/rk_wifi_ctrl.cpp
index 57911e7..6492c9a 100755
--- a/libwifi_hal/rk_wifi_ctrl.cpp
+++ b/libwifi_hal/rk_wifi_ctrl.cpp
@@ -67,6 +67,7 @@ static wifi_device supported_wifi_devices[] = {
        {"AP6356S",     "02d0:4356"},
        {"AP6335",      "02d0:4335"},
        {"AP6255",      "02d0:a9bf"},
+       {"AP6212",      "02d0:a9a6"},
        {"RTL8822BE",   "10ec:b822"},
        {"MVL88W8977",  "02df:9145"},
 };
diff --git a/libwifi_hal/wifi_hal_common.cpp b/libwifi_hal/wifi_hal_common.cpp
index 4639012..7b3acb3 100755
--- a/libwifi_hal/wifi_hal_common.cpp
+++ b/libwifi_hal/wifi_hal_common.cpp
@@ -149,6 +149,7 @@ wifi_ko_file_name module_list[] =
        {"AP6354",          BCM_DRIVER_MODULE_NAME,       BCM_DRIVER_MODULE_PATH, UNKKOWN_DRIVER_MODULE_ARG},
        {"AP6356S",         BCM_DRIVER_MODULE_NAME,       BCM_DRIVER_MODULE_PATH, UNKKOWN_DRIVER_MODULE_ARG},
        {"AP6255",          BCM_DRIVER_MODULE_NAME,       BCM_DRIVER_MODULE_PATH, UNKKOWN_DRIVER_MODULE_ARG},
+       {"AP6212",          BCM_DRIVER_MODULE_NAME,       BCM_DRIVER_MODULE_PATH, UNKKOWN_DRIVER_MODULE_ARG},
        {"APXXX",           BCM_DRIVER_MODULE_NAME,       BCM_DRIVER_MODULE_PATH, UNKKOWN_DRIVER_MODULE_ARG},
        {"MVL88W8977",      MVL_DRIVER_MODULE_NAME,       MVL_DRIVER_MODULE_PATH, MVL88W8977_DRIVER_MODULE_ARG},
         {"RK912",         RK912_DRIVER_MODULE_NAME,     RK912_DRIVER_MODULE_PATH, UNKKOWN_DRIVER_MODULE_ARG},

```










```
