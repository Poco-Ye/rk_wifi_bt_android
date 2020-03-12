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
