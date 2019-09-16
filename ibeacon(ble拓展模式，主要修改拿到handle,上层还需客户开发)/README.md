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
