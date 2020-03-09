太多这种问题了每次都要我手动敲不好


注意没有/sdcard/btsnoop_hci.log的话(sdcard不可用)，一定要用/data/misc/bluedroid/btsnoop_hci.log，selinux在init.rc就授权
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

测量一下LPO引脚有没有32.768k clk提供还有频偏，PMU 配置LDO提供的 VDDIO引脚的电平，VBAT引脚电平，BT_RTS_N使能引脚电平，还有晶体频偏

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

测量一下LPO引脚有没有32.768k clk提供还有频偏，PMU 配置LDO提供的 VDDIO引脚的电平，VBAT引脚电平，BT_RTS_N使能引脚电平，还有晶体频偏

echo 0 > /sys/class/rfkill/rfkill0/state
echo 1 > /sys/class/rfkill/rfkill0/state
BT_RTS_N引脚有无电平变化
```
```
蓝牙模板三：
setprop  persist.bluetooth.btsnoopenable  true

setprop  persist.bluetooth.btsnooppath   /sdcard/btsnoop_hci.log

关开蓝牙
复现问题提供一下
/sdcard/btsnoop_hci.log

```
蓝牙模板四：
```
diff --git a/include/vnd_rksdk.txt b/include/vnd_rksdk.txt
index 811cf25..7fef04e 100644
--- a/include/vnd_rksdk.txt
+++ b/include/vnd_rksdk.txt
@@ -15,8 +15,8 @@ BT_WAKE_VIA_PROC = TRUE
 SCO_PCM_ROUTING = 0
 SCO_PCM_IF_CLOCK_RATE = 2
 SCO_PCM_IF_FRAME_TYPE = 0
-SCO_PCM_IF_SYNC_MODE = 0
-SCO_PCM_IF_CLOCK_MODE = 0
+SCO_PCM_IF_SYNC_MODE = 1
+SCO_PCM_IF_CLOCK_MODE = 1
 PCM_DATA_FMT_SHIFT_MODE = 0
 PCM_DATA_FMT_FILL_BITS = 0
 PCM_DATA_FMT_FILL_METHOD = 0

将模组的PCM_IN PCM_OUT PCM_SYNC PCM_CLK 与声卡的连接断开，然后将模组的PCM_IN PCM_OUT进行短接

再用微信或者app语音测试，进行回环测试，手机上能否自己说话自己听到

用示波器抓一下PCM_SYNC PCM_CLK 两端,是否有clk，是声卡那边提供还是模组那边提供,clk的频率和峰峰值
```
蓝牙模板五：
```
使能脚电压和模组VDDIO电压是否一致，CPU sdio或者uart域电压和模组VDDIO电压是否一致

保证使能引脚 模组VDDIO   CPU sdio或者uart域电压 一致
```
```
wifi模板一：
测量一下LPO 引脚有无32.768k clk 还有频偏，测量WL_REG_ON电平 ，VDDIO电平 ,VBAT电平，还有晶体频偏

echo 0 > /sys/class/rkwifi/power
echo 1 > /sys/class/rkwifi/power

测量一下有无电平变化WL_REG_ON

 cat /d/clk/clk_summary (只有在节点上有clock name的才会显示，没有的就没有，比如设置clock frequency)
 
 find /d/ -name pinmux-pins 
 cat  pinmux-pins| grep mmc (sdio有时就是不知道用哪一个  有时候是sdio节点 有时候又sdmmc节点 这个要看看)
 
 wifi扫描不到经常是模组晶振频偏问题
 
 CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP =n (编译入kernel不是编译模块 去掉module init，extern出去 在sys接口上调用)
 echo 1 > /sys/class/rkwifi/driver
 
 查看打印出来的log看看问题
 
 
```




