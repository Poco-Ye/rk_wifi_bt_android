蓝牙库的加载
```
libbluetooth_jni.so 
==>System.loadLibrary("bluetooth_jni") ==>jniRegisterNativeMethods(env, "com/android/bluetooth/avrcp/Avrcp",sMethods, NELEM(sMethods));
==>src/com/android/bluetooth/avrcp/Avrcp.java==>class Avrcp {  static {classInitNative();}

bluetooth.default.so
bluetooth_rtk.default.so
==>hw_get_module("bluetooth", (hw_module_t const**)&module) ==> hardware/libhardware/hardware.c ==> handle=dlopen(path, RTLD_NOW)
==> hmi=(struct hw_module_t *)dlsym(handle, sym)

libbt-vendor.so
libbt-vendor_usb.so
libbt-vendor_uart.so
==>lib_handle = dlopen("libbt-vendor.so",RTLD_NOW)

RTK库版本问题
hardware/realtek/rtkbt$ grep 20170109 -nr
code/libbt-vendor/uart/src/hardware.c:30:#define RTKBT_RELEASE_NAME "20170109_TV_ANDROID_7.x"
code/libbt-vendor/uart/src/bt_vendor_rtk.c:29:#define RTKBT_RELEASE_NAME "20170109_TV_ANDROID_7.x"
code/libbt-vendor/usb/src/bt_vendor_rtk.c:28:#define RTKBT_RELEASE_NAME "20170109_TV_ANDROID_7.x"
system/etc/bluetooth/rtkbt.conf:1:# RELEASE NAME: 20170109_TV_ANDROID_7.x
rtkbt.mk:1:# RELEASE NAME: 20170109_TV_ANDROID_7.x

module的ID也必须和名字是一致的，所以拿到别人编译好的.so改个名字，是不行的，必须里面的.id名字也一致，这是因为有这个校验

所以你出现错误的原因就是改不了人家的ID，却要匹配自己的，可以按照人家的名字来改

库是存放在libhardware/hardware.c:36:#define HAL_LIBRARY_PATH1 "/system/lib/hw"
```
有时候不知道是加载32位的还是64位的

1、cat /proc/cpuinfo 

2、getprop |grep ro.product.cpu.abilist64
```



libhardware/hardware.c:32:#define HAL_LIBRARY_PATH1 "/system/lib64/hw"
libhardware/hardware.c:33:#define HAL_LIBRARY_PATH2 "/vendor/lib64/hw"
libhardware/hardware.c:34:#define HAL_LIBRARY_PATH3 "/odm/lib64/hw"
libhardware/hardware.c:36:#define HAL_LIBRARY_PATH1 "/system/lib/hw"
libhardware/hardware.c:37:#define HAL_LIBRARY_PATH2 "/vendor/lib/hw"
libhardware/hardware.c:38:#define HAL_LIBRARY_PATH3 "/odm/lib/hw"

31 #if defined(__LP64__)
32 #define HAL_LIBRARY_PATH1 "/system/lib64/hw"
33 #define HAL_LIBRARY_PATH2 "/vendor/lib64/hw"
34 #define HAL_LIBRARY_PATH3 "/odm/lib64/hw"
35 #else
36 #define HAL_LIBRARY_PATH1 "/system/lib/hw"
37 #define HAL_LIBRARY_PATH2 "/vendor/lib/hw"
38 #define HAL_LIBRARY_PATH3 "/odm/lib/hw"
39 #endif

31 #if defined(__LP64__)  


131 static int hw_module_exists(char *path, size_t path_len, const char *name,
132 const char *subname)
133 {
134     snprintf(path, path_len, "%s/%s.%s.so",
135     HAL_LIBRARY_PATH3, name, subname);
136     if (access(path, R_OK) == 0)
137     return 0;
138
139     snprintf(path, path_len, "%s/%s.%s.so",
140     HAL_LIBRARY_PATH2, name, subname);
141     if (access(path, R_OK) == 0)
142     return 0;
143
144     snprintf(path, path_len, "%s/%s.%s.so",
145     HAL_LIBRARY_PATH1, name, subname);
146     if (access(path, R_OK) == 0)
147     return 0;
148
149     return -ENOENT;
150 }


static int load(const char *id,
69 const char *path,
70 const struct hw_module_t **pHmi)
71 {
72 int status = -EINVAL;
73 void *handle = NULL;
74 struct hw_module_t *hmi = NULL;
75
76 /*
77 * load the symbols resolving undefined symbols before
78 * dlopen returns. Since RTLD_GLOBAL is not or'd in with
79 * RTLD_NOW the external symbols will not be global
80 */
81 handle = dlopen(path, RTLD_NOW);
82 if (handle == NULL) {
83 char const *err_str = dlerror();
84 ALOGE("load: module=%s\n%s", path, err_str?err_str:"unknown");
85 status = -EINVAL;
86 goto done;
87 }
88
89 /* Get the address of the struct hal_module_info. */
90 const char *sym = HAL_MODULE_INFO_SYM_AS_STR;
91 hmi = (struct hw_module_t *)dlsym(handle, sym);
92 if (hmi == NULL) {
93 ALOGE("load: couldn't find symbol %s", sym);
94 status = -EINVAL;
95 goto done;
96 }
97
98 /* Check that the id matches */
99 if (strcmp(id, hmi->id) != 0) {
100 ALOGE("load: id=%s != hmi->id=%s", id, hmi->id);
101 status = -EINVAL;
102 goto done;
103 }

100 ALOGE("load: id=%s != hmi->id=%s", id, hmi->id);  这个就是校验id和库的名字是必须一致的


yebin@ubuntu:~/RK3229_Android7.1_Box_20190723/hardware$ grep BT_HARDWARE_RTK_MODULE_ID -nr
realtek/rtkbt/code/bt_bak/btif/src/bluetooth.c:602:    .id = BT_HARDWARE_RTK_MODULE_ID,
realtek/rtkbt/code/bt_bak/service/hal/bluetooth_interface.cpp:267:    status = module->methods->open(module, BT_HARDWARE_RTK_MODULE_ID, &device);
libhardware/include/hardware/bluetooth.h:36:#define BT_HARDWARE_RTK_MODULE_ID "bluetooth_rtk"

所以新的库移植到RK

diff --git a/btif/src/bluetooth.c b/btif/src/bluetooth.c
index ede3dcc..5d83be1 100755
--- a/btif/src/bluetooth.c
+++ b/btif/src/bluetooth.c
@@ -600,7 +600,7 @@ EXPORT_SYMBOL struct hw_module_t HAL_MODULE_INFO_SYM = {
     .tag = HARDWARE_MODULE_TAG,
     .version_major = 1,
     .version_minor = 0,
-    .id = BT_HARDWARE_MODULE_ID,
+    .id = BT_HARDWARE_RTK_MODULE_ID,
     .name = "Bluetooth Stack",
     .author = "The Android Open Source Project",
     .methods = &bt_stack_module_methods
diff --git a/service/hal/bluetooth_interface.cpp b/service/hal/bluetooth_interface.cpp
index a551fee..2814e1b 100755
--- a/service/hal/bluetooth_interface.cpp
+++ b/service/hal/bluetooth_interface.cpp
@@ -264,7 +264,7 @@ class BluetoothInterfaceImpl : public BluetoothInterface {

     // Open the Bluetooth adapter.
     hw_device_t* device;
-    status = module->methods->open(module, BT_HARDWARE_MODULE_ID, &device);
+    status = module->methods->open(module, BT_HARDWARE_RTK_MODULE_ID, &device);
     if (status) {
       LOG(ERROR) << "Failed to open the Bluetooth module";
       return false;








```
