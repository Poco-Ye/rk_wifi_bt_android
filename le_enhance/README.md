```
查2001指令，HCI_LE_Enhanced_Connection_Complete默认设置为支持，disable掉第二个字节第二位

sdk_project@aaaaa:~/7.1_sdk/RK3288_ANDROID7.1_TABLET-SDK_V1.00_20170629/system/bt/device/src$ git diff .
diff --git a/device/src/controller.c b/device/src/controller.c
index 4440ea5..6663569 100644
--- a/device/src/controller.c
+++ b/device/src/controller.c
@@ -30,7 +30,7 @@
 #include "osi/include/future.h" 
 #include "stack/include/btm_ble_api.h" 

-const bt_event_mask_t BLE_EVENT_MASK = { "\x00\x00\x00\x00\x00\x00\x06\x7f" };
+const bt_event_mask_t BLE_EVENT_MASK = { "\x00\x00\x00\x00\x00\x00\x04\x7f" };

 #if (BLE_INCLUDED)
 const bt_event_mask_t CLASSIC_EVENT_MASK = { HCI_DUMO_EVENT_MASK_EXT };
```

```
或者加上图上的命令
```
