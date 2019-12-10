```
--- a/drivers/bluetooth/rtk_btusb.c
+++ b/drivers/bluetooth/rtk_btusb.c
@@ -33,7 +33,7 @@
 #include "rtk_btusb.h" 
 #define VERSION "2.21" 

-#define DBG_FLAG 0
+#define DBG_FLAG 1
 #if DBG_FLAG
 #define RTKBT_DBG(fmt, arg...) printk(KERN_INFO "rtk_btusb: " fmt "\n" , ## arg)
 #else
 
 这个是打开Log
 
 我们驱动改了东西
 
 check_fw_version 主要是看模组的fw还在不在，不在才进行download 主要是下1001 cmd 如果是same 那就是没又掉 不下载
 
 那什么时候开始下？看这个download_patch函数是放在ioctl的后面我们改为放在open，下载fw前要先用check_fw_version看看fw有没有掉
 下了fw 和没有下fw 1001读出来的东西不一样的
 
 
HCI_Version: Bluetooth Core Specification 4.0
HCI_Revision: 0x1e6c
LMP/PAL_Version: Bluetooth Core Specification 4.0
Manufacturer_Name: Realtek Semiconductor Corporation
LMP/PAL_Subversion: 0xa747

 
 
 
```
