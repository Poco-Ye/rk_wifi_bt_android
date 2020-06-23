```
随着工程越来越大，是一定会分模块的，彼此之间肯定有独立的
过滤log TAG 直接看对应文件或者模块的log，单独分析模块，这样舒服一点看大的工程

kernel
printk(KERN_ERR "TAG_poco%s %s %d \n",__FILE__,__FUNCTION__,__LINE__);
printk(KERN_ERR "TAG_poco: %s xxx %d xxx %d\n",xxx, xxx, xxx);
printk(KERN_WARNING "TAG_poco: %s xxx %d\n", xxx, xxx);

hardware
#define LOG_TAG "TAG_poco"
ALOGE("%s xxx %04x", __FUNCTION__, xxx);
ALOGW("xxx %s", xxx);

package

public static final boolean DEBUG = true;
public static final boolean VERBOSE = true;

private static final String TAG = "TAG_poco"
Log.e(TAG, "xxx=" + xxx + " xxx=" + xxx);








```
