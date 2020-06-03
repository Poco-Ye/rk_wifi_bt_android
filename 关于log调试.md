```
这个两个东西可以在android上找到调试
grep "Log." -nr
grep  ALOG   -nr



linux的话没那么规范，以printk或者printf为define，自己找，一般一个软件
#define RTKBT_DBG_FLAG          0

#if RTKBT_DBG_FLAG
#define RTKBT_DBG(fmt, arg...) printk(KERN_INFO "rtk_btusb: " fmt "\n" , ## arg)
#else
#define RTKBT_DBG(fmt, arg...)

rtk_btusb.h:76:#define RTKBT_INFO(fmt, arg...) printk(KERN_INFO "rtk_btusb: " fmt "\n" , ## arg)


还有可能放在Makefile的  -D上


linux的主要看看kernel的
kernel/include/linux/kern_levels.h

#define KERN_EMERG      KERN_SOH "0"    /* system is unusable */
#define KERN_ALERT      KERN_SOH "1"    /* action must be taken immediately */
#define KERN_CRIT       KERN_SOH "2"    /* critical conditions */
#define KERN_ERR        KERN_SOH "3"    /* error conditions */
#define KERN_WARNING    KERN_SOH "4"    /* warning conditions */
#define KERN_NOTICE     KERN_SOH "5"    /* normal but significant condition */
#define KERN_INFO       KERN_SOH "6"    /* informational */
#define KERN_DEBUG      KERN_SOH "7"    /* debug-level messages */

#define KERN_DEFAULT    KERN_SOH "d"    /* the default kernel loglevel */

cat /proc/sys/kernel/printk
7417
echo 4 >/proc/sys/kernel/printk
4417

这个东西其实是过滤的作用，并不是说软件上打的log丢失了，没有丢失，没有丢失，而是不显示在终端，
dmesg一样可以看到的，logcat也可以看到调试的，只不过没有直接就输出到终端


那现在有这么一个新的软件，或者某一项功能，那就要从log开始

蓝牙可以找到进程
ps |grep bluetooth
logcat |grep bluetoth-id

wifi 以太网可就没那么好了，进程多的是

在hardware jni
c、c++层调用：在c,c++层包含此头文件：#include <cutils/log.h>，
在需要调用Log的地方执行：ALOGV,ALOGD,ALOGI,ALOGW,ALOGE

然后在每一个要打log文件都有

所以grep ALOG -nr 
#define LOG_TAG "xxx"

在framkwork app
java层调用：在java层调用import android.util.Log，
在需要打印Log的地方执行Log.v,Log.d,Log.i,Log.w,Log.e

然后在每一个要打log文件都有
    private static final String TAG = "xxx";
    private static final boolean DBG = false;
    private static final boolean VDBG = false;


if(DBG)
Log. 

if(VDBG)
Log.



TAG默认是""

TAG需要有xxx的含义好调试，如果没有定义就是""


所以log以TAG为核心，没有的话就没有办法了，有TAG好调，有

有TAG好的

我们的目标就是找TAG


我们遇到新的问题，是PLOG打不了DEBUG的log，还有Log.d 也有可能没有打出log



这部分的实现模块是system/core/liblog  最终实现函数是printf

听说有 setprop log.tag.TAG 'D'  这种方式，可以保证debug的log 打出来

具体实现就要分析log模块了，目前PLOG也打不出。。。其它模块只能是重新#define LOG_TAG并调用模块函数


system/core/liblog/logger_write.c
  93 static android_LogPriority filterCharToPri (char c)
  94 {
  95     android_LogPriority pri;
  96
  97     c = tolower(c);
  98
  99     if (c >= '0' && c <= '9') {
 100         if (c >= ('0'+ANDROID_LOG_SILENT)) {
 101             pri = ANDROID_LOG_VERBOSE;
 102         } else {
 103             pri = (android_LogPriority)(c - '0');
 104         }
 105     } else if (c == 'v') {
 106         pri = ANDROID_LOG_VERBOSE;
 107     } else if (c == 'd') {
 108         pri = ANDROID_LOG_DEBUG;
 109     } else if (c == 'i') {
 110         pri = ANDROID_LOG_INFO;
 111     } else if (c == 'w') {
 112         pri = ANDROID_LOG_WARN;
 113     } else if (c == 'e') {
 114         pri = ANDROID_LOG_ERROR;


```
