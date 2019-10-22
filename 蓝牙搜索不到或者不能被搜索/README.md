
蓝牙搜索和配对过程主要有两种

一种是BR/EDR的 一种是BLE的 频道是不一样的 可以理解成两个设备

```
BR/EDR 的搜索是主动的方式，往空中散发inquiry ID packet，对端回inquiry result packet
BLE的搜索是被动的方式，就是扫描空中散发的广播包，然后发connection indication packet进行连接

Linux:

BR/EDR:
打开扫描
hciconfig hci0 iscan
打开配对
hciconfig hci0 pscan
同时打开扫描和配对
hciconfig hci0 piscan
同时关闭扫描和配对（不能被发现）
hciconfig hci0 noscan

BLE:
打开广播
hciconfig hci0 leadv
关闭广播
hciconfig hci0 noleadv
打开扫描
hcitool -i hci0 lescan
关闭扫描
hciconfig hci0 noscan

android默认只有inquirying、inquiry scan、lescan没有le adv，搜索不到就是指的是BR/EDR设备搜索不到
```

1、搜索不到，天线信号不好，增加inquiry时间
```
diff --git a/btif/src/btif_dm.c b/btif/src/btif_dm.c
index f54b6427..43dda023 100644
--- a/btif/src/btif_dm.c
+++ b/btif/src/btif_dm.c
@@ -80,7 +80,7 @@
 #define COD_AV_HIFI_AUDIO                   0x0428

 #define BTIF_DM_DEFAULT_INQ_MAX_RESULTS     0
-#define BTIF_DM_DEFAULT_INQ_MAX_DURATION    10
+#define BTIF_DM_DEFAULT_INQ_MAX_DURATION    15
 #define BTIF_DM_MAX_SDP_ATTEMPTS_AFTER_PAIRING 2

 #define NUM_TIMEOUT_RETRIES                 5


nquriy Time = N*1.28 sec,  15 * 1.28 =19.2s 默认是12.8s
N Range:1 ~ 48  ， time range: 1.28s~61.44s
```

2、天线信号不好，增加发现设备时间
```
diff --git a/include/bt_target.h b/include/bt_target.h
index b0cf8566..574fb14f 100644
--- a/include/bt_target.h
+++ b/include/bt_target.h
@@ -352,7 +352,7 @@

 /* The size in bytes of the BTM inquiry database. */
 #ifndef BTM_INQ_DB_SIZE
-#define BTM_INQ_DB_SIZE             40
+#define BTM_INQ_DB_SIZE             80
 #endif

 /* The default scan mode */

当设备inquiry之后（默认是12.8s）就会对inquiry result去拿设备名，天线信号不好，容易timeout，搜索不到设备



```

不能被搜索到或者连不上天线信号不好：
1、am start -a android.bluetooth.adapter.action.REQUEST_DISCOVERABLE
开启可被发现
```
cat /data/misc/bluedroid/bt_config.conf 可找到DiscoveryTimeout有设置就不用再设
```
2、
```
--- a/include/bt_target.h
+++ b/include/bt_target.h
@@ -367,7 +367,7 @@

 /* Sets the Page_Scan_Window:  the length of time that the device is performing a page scan. */
 #ifndef BTM_DEFAULT_CONN_WINDOW
-#define BTM_DEFAULT_CONN_WINDOW     0x0012
+#define BTM_DEFAULT_CONN_WINDOW     0x0064
 #endif

 /* Sets the Page_Scan_Activity:  the interval between the start of two consecutive page scans. */
@@ -377,12 +377,12 @@

 /* When automatic inquiry scan is enabled, this sets the inquiry scan window. */
 #ifndef BTM_DEFAULT_DISC_WINDOW
-#define BTM_DEFAULT_DISC_WINDOW     0x0012
+#define BTM_DEFAULT_DISC_WINDOW     0x0064
 #endif

 /* When automatic inquiry scan is enabled, this sets the inquiry scan interval. */
 #ifndef BTM_DEFAULT_DISC_INTERVAL
-#define BTM_DEFAULT_DISC_INTERVAL   0x0800
+#define BTM_DEFAULT_DISC_INTERVAL   0x1000
 #endif

实验过比较好的参数，
inquiry window inquiry interval
62.5ms 2.56s
page scan window page scan interval
62.5ms 1.28s

如果还是不行请找模组代理商进行RF测试或者替换fw

```
