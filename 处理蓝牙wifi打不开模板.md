太多这种问题了每次都要我手动敲不好

```
蓝牙模板一：
修改文件/etc/bluetooth/bt_stack.conf
diff --git a/bt_stack.conf b/bt_stack.conf
index 711fe51..280d4bd 100644
--- a/bt_stack.conf
+++ b/bt_stack.conf
@@ -1,6 +1,6 @@
 # Enable BtSnoop logging function
 # valid value : true, false
-BtSnoopLogOutput=false
+BtSnoopLogOutput=true

 # BtSnoop log output file
 BtSnoopFileName=/sdcard/btsnoop_hci.log
 
 
改完后chmod 777  /etc/bluetooth/bt_stack.conf
关闭再打开蓝牙
复现问题提供一下/sdcard/btsnoop_hci.log

测量一下LPO引脚有没有32.768k clk提供还有频偏，PMU 配置LDO提供的 VDDIO引脚的电平，VBAT引脚电平，BT_RTS_N使能引脚电平

echo 0 > /sys/class/rfkill/rfkill0/state
echo 1 > /sys/class/rfkill/rfkill0/state
BT_RTS_N引脚有无电平变化
 
```

```
蓝牙模板二：
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
复现问题提供一下/sdcard/btsnoop_hci.log

测量一下LPO引脚有没有32.768k clk提供还有频偏，PMU 配置LDO提供的 VDDIO引脚的电平，VBAT引脚电平，BT_RTS_N使能引脚电平

echo 0 > /sys/class/rfkill/rfkill0/state
echo 1 > /sys/class/rfkill/rfkill0/state
BT_RTS_N引脚有无电平变化
```
