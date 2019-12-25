打开bluedroid log:
```
diff --git a/bt_stack.conf b/bt_stack.conf
index 711fe51..0d62aed 100644
--- a/bt_stack.conf
+++ b/bt_stack.conf
@@ -1,6 +1,6 @@
 # Enable BtSnoop logging function
 # valid value : true, false
-BtSnoopLogOutput=false
+BtSnoopLogOutput=true

 # BtSnoop log output file
 BtSnoopFileName=/sdcard/btsnoop_hci.log
@@ -20,19 +20,19 @@ TraceConf=true
 #   BT_TRACE_LEVEL_EVENT   4    ( Debug messages for events )
 #   BT_TRACE_LEVEL_DEBUG   5    ( Full debug messages )
 #   BT_TRACE_LEVEL_VERBOSE 6    ( Verbose messages ) - Currently supported for TRC_BTAPP only.
-TRC_BTM=2
-TRC_HCI=2
-TRC_L2CAP=2
-TRC_RFCOMM=2
-TRC_OBEX=2
-TRC_AVCT=2
-TRC_AVDT=2
-TRC_AVRC=2
-TRC_AVDT_SCB=2
-TRC_AVDT_CCB=2
-TRC_A2D=2
-TRC_SDP=2
-TRC_GATT=2
-TRC_SMP=2
-TRC_BTAPP=2
-TRC_BTIF=2
+TRC_BTM=6
+TRC_HCI=6
+TRC_L2CAP=6
+TRC_RFCOMM=6
+TRC_OBEX=6
+TRC_AVCT=6
+TRC_AVDT=6
+TRC_AVRC=6
+TRC_AVDT_SCB=6
+TRC_AVDT_CCB=6
+TRC_A2D=6
+TRC_SDP=6
+TRC_GATT=6
+TRC_SMP=6
+TRC_BTAPP=6
+TRC_BTIF=6

改完后chmod 777  /etc/bluetooth/bt_stack.conf
关闭再打开蓝牙
复现问题提供一下/sdcard/btsnoop_hci.log和logcat log
```
打开hci_module_hardware log:
```
--- a/include/vnd_rk30sdk.txt
+++ b/include/vnd_rk30sdk.txt
@@ -4,10 +4,10 @@ UART_TARGET_BAUD_RATE = 1500000
 FW_PATCH_SETTLEMENT_DELAY_MS = 200
 USERIAL_VENDOR_SET_BAUD_DELAY_US = 200000
 LPM_IDLE_TIMEOUT_MULTIPLE = 5
-BTVND_DBG = FALSE
+BTVND_DBG = TRUE
 BTHW_DBG = TRUE
-VNDUSERIAL_DBG = FALSE
-UPIO_DBG = FALSE
+VNDUSERIAL_DBG = TRUE
+UPIO_DBG = TRUE
 USE_CONTROLLER_BDADDR = TRUE
 FW_AUTO_DETECTION = TRUE
 BT_WAKE_VIA_PROC = TRUE
```
打开rfkill log
```
diff --git a/net/rfkill/rfkill-bt.c b/net/rfkill/rfkill-bt.c
index 06963b6a2bb..73711172ae3 100755
--- a/net/rfkill/rfkill-bt.c
+++ b/net/rfkill/rfkill-bt.c
@@ -40,7 +40,7 @@
 #include <linux/of_gpio.h>
 #endif

-#if 0
+#if 1
 #define DBG(x...)   printk(KERN_INFO "[BT_RFKILL]: "x)
 #else
 #define DBG(x...)

```

