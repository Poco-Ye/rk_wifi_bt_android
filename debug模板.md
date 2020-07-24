```
kernel
printk(KERN_ERR "TAG_poco%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
printk(KERN_ERR "TAG_poco: %s xxx %d xxx %d\n",xxx, xxx, xxx);
printk(KERN_WARNING "TAG_poco: %s xxx %d\n", xxx, xxx);

hardware
#define LOG_NDEBUG 0   //针对目标TAG
#define LOG_TAG "TAG_poco"
ALOGE("%s xxx %04x", __FUNCTION__, xxx);
ALOGW("xxx %s", xxx);


package&&framkwork
使用命令setprop log.tag.TAG_poco V  //针对目标TAG
private static final String TAG = "TAG_poco"
private static final boolean DBG = true;
private static final boolean DDBG = Log.isLoggable(TAG, Log.DEBUG);
private static final boolean VDBG = Log.isLoggable(TAG, Log.VERBOSE);
if(DDBG||VDBG)
Log.d(TAG, "xxx=" + xxx + " xxx=" + xxx);


```
