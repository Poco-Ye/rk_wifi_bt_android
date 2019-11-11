07-16 06:38:27.806 E/bt_osi_alarm( 1404): timer_create_internal unable to create timer with clock 9: Unknown error 524

07-16 06:38:27.806 E/bt_osi_alarm( 1404): The kernel might not have support for timer_create(CLOCK_BOOTTIME_ALARM): https://lwn.net/Articles/429925/

07-16 06:38:27.807 E/bt_osi_alarm( 1404): See following patches: https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/log/?qt=grep&q=CLOCK_BOOTTIME_ALARM



```
bluedroid clock要去系统拿32.768k
1、rk808 dts确保已配
clocks = <&rk808 1>;
clock-names = "ext_clock";
或者hym8563
clocks = <&hym8563>;
clock-names = "ext_clock";

如果不行
2、
若不行就去掉

diff --git a/osi/src/alarm.cc b/osi/src/alarm.cc
index 9bf9cc5f8..f360f683c 100644
--- a/osi/src/alarm.cc
+++ b/osi/src/alarm.cc
@@ -115,11 +115,11 @@ struct alarm_t {
 int64_t TIMER_INTERVAL_FOR_WAKELOCK_IN_MS = 3000;
 static const clockid_t CLOCK_ID = CLOCK_BOOTTIME;

-#if (KERNEL_MISSING_CLOCK_BOOTTIME_ALARM == TRUE)
+//#if (KERNEL_MISSING_CLOCK_BOOTTIME_ALARM == TRUE)
 static const clockid_t CLOCK_ID_ALARM = CLOCK_BOOTTIME;
-#else
-static const clockid_t CLOCK_ID_ALARM = CLOCK_BOOTTIME_ALARM;
-#endif
+//#else
+//static const clockid_t CLOCK_ID_ALARM = CLOCK_BOOTTIME_ALARM;
+//#endif

 // This mutex ensures that the |alarm_set|, |alarm_cancel|, and alarm callback
 // functions execute serially and not concurrently. As a result, this mutex
重新编system
```
