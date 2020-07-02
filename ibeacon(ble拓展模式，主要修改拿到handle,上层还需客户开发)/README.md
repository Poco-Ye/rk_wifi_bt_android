按照这里提供 按照这里提供
```
-------------按分割线提供
external/bluetooth/bluedroid/include/bt_target.h
--- a/include/bt_target.h
++ b/include/bt_target.h
-1339,7 +1339,7 and USER_HW_DISABLE_API macros / * feature discovery, multi-adv etc.
/
#ifndef BLE_VND_INCLUDED
-#define BLE_VND_INCLUDED FALSE
+#define BLE_VND_INCLUDED TRUE
#endif


frameworks/base/core/res/res/values/config.xml
config_bluetooth_le_peripheral_mode_supported = true
如果device/rockchip/common/overlay/packages/apps/Bluetooth/res/values/config.xml中也有定义config_bluetooth_le_peripheral_mode_supported的话，也要修改
mmm packages/apps/Bluetooth/ -B



--- a/core/java/android/bluetooth/BluetoothAdapter.java
+++ b/core/java/android/bluetooth/BluetoothAdapter.java
@@ -570,7 +570,7 @@ public final class BluetoothAdapter {
      */
     public BluetoothLeAdvertiser getBluetoothLeAdvertiser() {
         if (!getLeAccess()) return null;
-        if (!isMultipleAdvertisementSupported() && !isPeripheralModeSupported()) {
+        if (/*!isMultipleAdvertisementSupported() &&*/ !isPeripheralModeSupported()) {
             Log.e(TAG, "Bluetooth LE advertising not supported");
             return null;
         }
         
-------------按分割线提供
```


如果还不行就找一下redmine 还有就是打下面的补丁

```
diff --git a/src/com/android/bluetooth/btservice/AdapterService.java b/src/com/android/bluetooth/btservice/AdapterService.java
index 0c3e501..bf2eb5a 100644
--- a/src/com/android/bluetooth/btservice/AdapterService.java
+++ b/src/com/android/bluetooth/btservice/AdapterService.java
@@ -1688,7 +1688,7 @@ public class AdapterService extends Service {

     public boolean isMultiAdvertisementSupported() {
         enforceCallingOrSelfPermission(BLUETOOTH_PERM, "Need BLUETOOTH permission");
-        return getNumOfAdvertisementInstancesSupported() >= MIN_ADVT_INSTANCES_FOR_MA;
+        return true;//getNumOfAdvertisementInstancesSupported() >= MIN_ADVT_INSTANCES_FOR_MA;
     }

     public boolean isRpaOffloadSupported() {

--- a/include/bt_target.h
++ b/include/bt_target.h
-1339,7 +1339,7 and USER_HW_DISABLE_API macros / * feature discovery, multi-adv etc.
/
#ifndef BLE_VND_INCLUDED
-#define BLE_VND_INCLUDED FALSE
+#define BLE_VND_INCLUDED TRUE
#endif
```

```
发送和接收ble advertiser的参考资料

http://blog.csdn.net/lansefeiyang08/article/details/46482073
https://www.cnblogs.com/CharlesGrant/p/7155211.html
https://race604.com/android-ble-in-action/

如何创建GATTServer
https://blog.csdn.net/sinat_19628093/article/details/51789617?locationNum=10
```
