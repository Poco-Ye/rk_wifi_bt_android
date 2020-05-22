关于dmesg或者logcat |grep -e -e -e 的问题可以研究各种嵌入式各个部分的问题，关于.repo/repo/repo sync -c xxx -no-tags和git stash gis stash pop可以管理嵌入式各个部分的问题

蓝牙问题主要先在snoop找到连接开头的地方，然后baseband或者linklayer cmd/complete cmd-reply/complete和l2cap都可以并列进行，关于link的问题最好看文案表，关于L2CAP以上问题最好看chart，非常直观，有可能出现在link（包括link control control&baseband  link policy）上，出现在link上问题经常换fw或者改地址，出现l2cap可能是软件上或者也有可能通信干扰


SDK编译问题，直接修改build.sh的all选项，涵盖了所有的部分，可以屏蔽或者加echo，可以单项测试

WIFI FTP

http://rsc.realtek.com

帐号：rockchip_lch 密码：rockchip123

这个上面一样放到ftp3.realtek.com  这个上面放了android各种wifi 蓝牙资源  不同账户和密码拿的东西不一样

BT FTP

ftp://ftp3.realtek.com

账号bt	 密码V9nW2h



看上层代码的诀窍是只看后面函数不看前面的类，查看复用以0A 0B 0C 0D 1A..系列为查询比如GRF_GPIO1A_IOMUX 0x0010

1、io命令的例子io -4 -w 0xff7b0004 0x00ff000f   一定要0x 不然会报错

io -4 -r 0x20088004    

io -4 -l 12 0xff770024

先找mapping  再找group

例子3288 

GPIO0 0xff750000 GPIO1 0xff780000 GPIO2 0xff790000

组织列表，首先group第一个开始的就是DR（数据）寄存器，然后是DDR（方向）寄存器

GPIO_SWPORTA_DR 0x0000 W 0x00000000 Port A data register

GPIO_SWPORTA_DDR 0x0004 W 0x00000000 Port A data direction register

这个就是group表 io -4 0xff750000  读的就是引脚的电平  io -4 0xff750004  读的就是引脚的方向
```
四步走
第一步：找mapping
第二步：找group
第三步：dts找引脚
第四步：reganalyzer分析
```

2、概率性打不开蓝牙，替换8250驱动（kernel/drivers/tty/serial/8250），dma打开，博通默认打开流控，或者文件传输出问题
```
097  1466  1493 E bt_hci_h4: event_uart_has_bytes Unknown HCI message type 0x0 (min=0x2 max=0x4). Aborting...
07-03 07:20:24.099  1466  1493 F libc    : system/bt/hci/src/hci_hal_h4.c:241: event_uart_has_bytes: assertion "f
```
```
--- a/arch/arm/boot/dts/rk3288-box.dts
+++ b/arch/arm/boot/dts/rk3288-box.dts
@@ -351,8 +351,9 @@

 &uart_bt {
         status = "okay";
-        dma-names = "!tx", "!rx";      //打开dma
+        dma-names = "tx", "rx";
         pinctrl-0 = <&uart0_xfer &uart0_cts>;
+       dmas=<&dmac_peri 1>,<dmac_peri 2>; //不同芯片的这个dma配置不同，需要查看芯片手册，可以参考串口的手册的指导
 };

--- a/hci/src/hci_hal_h4.c
+++ b/hci/src/hci_hal_h4.c

-     assert(false && "Unknown HCI message type");
     
+     //assert(false && "Unknown HCI message type");
```
```
传输文件也是替换驱动，之类，绝大多少是因为波特率不准造成的，更换波特率比较好，类似2M
```

3、苹果br/edr inquiry不到或者连不到设备蓝牙，苹果手机会过滤掉作source的设备，改成作sink就行 
```
<bool name ="profile_supported_a2dp">false</bool>
<bool name ="profile_supported_a2dp_sink">true</bool>

/system/bt/include/bt_target.h

#define USE_AUDIO_TRACK TRUE
#ifndef BTA_AV_SINK_INCLUDED
#define BTA_AV_SINK_INCLUDED TRUE
#enif
```

4、设备扫不到其它手机

天线有问题，可以通话扫描inquiry scan的时间来补偿
```
inquiry window  inquiry interval

0x0012             0x0800      11.25ms  1.28s

0x0012             0x0400      11.25ms  0.64s

0x0024             0x0400      22.5ms   0.64s

100                4096        62.5ms   2.56s

配对不上

page scan window   page scan interval 

100                2048        62.5ms   1.28s

le scan

le scan window   le scan interval

16                 352         10ms     0.22s   
```



5、mmc2: new high speed SDIO card at address 0001 扫卡是可以了 说明cmd线是好的

SSV6XXX_SDIO mmc2:0001:1: sdio read reg write address failed (-110) 驱动读模组reg出现错误  data线有问题

这个可以打开log来看
```
--- a/drivers/mmc/host/rk_sdmmc_dbg.c
+++ b/drivers/mmc/host/rk_sdmmc_dbg.c
@@ -11,6 +11,6 @@

 #include "rk_sdmmc_dbg.h"

-u32 mmc_debug_level= MMC_DBG_BOOT|MMC_DBG_ERROR;
-char dbg_flag[]="mmc0mmc1mmc2";
+u32 mmc_debug_level= MMC_DBG_BOOT|MMC_DBG_ALL;
+char dbg_flag[]="mmc2";
```
6、iwlist看一下支不支持 monitor mode，monitor mode主要用来抓包需要模组商给新的驱动

ifconfig wlan0 down

iwconfig wlan0 mode monitor

ifconfig wlan0 up


7、am start -a android.bluetooth.adapter.action.REQUEST_DISCOVERABLE打开被发现
```
　　service call bluetooth_manager 8  关闭蓝牙

　　service call bluetooth_manager 6  打开蓝牙
```
8、PMU对wifi蓝牙的作用
```
直接在dts上找regulator-name
cat sys/class/regulator/regulator.6/name(例如)
cd  sys/class/regulator/regulator.6/name
cat *

PMU提供DCDC电压（3.3~4.2V）给模组的VDD  提供LDO 电压（1.8V或者3.3V给VDDIO） 同时也设置CPU IO（串口和sdio）
域电压1.8或者3.3V 还有LPO 32.768K给模组 
sdio_vref = <1800>; //1800mv or 3300mv
如果3288 wifi概率性起不来（312x sdio_vref没有作用），就需要检查一下vddio设置的对不对
模组（单片机）一共有两个电源口，一个是VDD还有一个是VDDIO，VDD正常都是3.3V或者以上的，基本不用管，VDDIO可以配置
如下就是配置vcc_wl配置VDDIO的电压（配置模组的IO电压），但是，CPU的sdio或者uart是否也要配置IO的电压，然后一起对应的上
经常遇到说串口不稳定，串口的域电压在哪里配置，WIFI的域电压在sdio_vref

diff --git a/rk3288-ennoconn.dts b/rk3288-ennoconn.dts
index 068c32f..aaee757 100644
--- a/rk3288-ennoconn.dts
+++ b/rk3288-ennoconn.dts
                                regulator-min-microvolt = <1800000>;
-                               regulator-max-microvolt = <3300000>;
+                               regulator-max-microvolt = <1800000>;
                                regulator-name = "vcc_wl";
                                
diff --git a/rk3288-evb.dtsi b/rk3288-evb.dtsi
--- a/rk3288-evb.dtsi
+++ b/rk3288-evb.dtsi
@@ -205,7 +205,7 @@
                compatible = "wlan-platdata";
                wifi_chip_type = "rtl8821cs";
-               sdio_vref = <3300>;
+               sdio_vref = <1800>;
```
9、sdio高速降成低速
```
wifi驱动是可以从上往下调编译成.ko的，具体看obj-的宏，每个版本不一样
CONFIG_AP6XXX=m
其它就是看
driver/wireless/rockchip_wlan/rkwifi/bcmdhd/dhd_linux.c
CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP（优先级第二）
CONFIG_WIFI_BUILD_MODULE（优先级最高）

&sdio0 {
 clock-frequency = <50000000>;  //降成50M
 clock-freq-min-max = <200000 50000000>;
 supports-sdio;
 bus-width = <4>;
 disable-wp;
 cap-sd-highspeed; //这个要加，sdio3.0的能力
 cap-sdio-irq;
 keep-power-in-suspend;
 mmc-pwrseq = <&sdio_pwrseq>;
 non-removable;
 num-slots = <1>;
 pinctrl-names = "default";
 pinctrl-0 = <&sdio0_bus4 &sdio0_cmd &sdio0_clk>;
 //sd-uhs-sdr104;   //这个要关掉，sdr104是208M的意思，我们CPU最多150M
 status = "okay";
};

查看sdio速率修改.md
```

10、复用关系查找（发现有复用可以将复用模块status设置成为disabled）
```
用io指令找出来不对，但是脑子联想到gpio的request那边去了，智商降低
应该过滤rockchip-pinctrl（kernel log ）
复用是pinctrl子系统去做的，不是request函数...看到iomux 不对 都是设成gpio的，就很慌，用io -w 去搞，并不是解决的办法...
如果rockchip-pinctrl找不到复用问题，iomux又都是gpio，那就是没有驱动没有运行下去由于其它原因或者根本就没跑...

[    2.188799] rockchip-pinctrl 20008000.pinctrl: pin gpio0-3 already requested by 20056000.i2c; cannot claim for 10218000.rksdmmc
[    2.188817] rockchip-pinctrl 20008000.pinctrl: pin-3 (10218000.rksdmmc) status -22
[    2.188831] rockchip-pinctrl 20008000.pinctrl: could not request pin 3 on device rockchip-pinctrl
[    2.190136] rockchip-pinctrl 20008000.pinctrl: pin gpio0-3 already requested by 20056000.i2c; cannot claim for 10218000.rksdmmc
[    2.190154] rockchip-pinctrl 20008000.pinctrl: pin-3 (10218000.rksdmmc) status -22
[    2.190167] rockchip-pinctrl 20008000.pinctrl: could not request pin 3 on device rockchip-pinctrl
[    2.190215] rockchip-pinctrl 20008000.pinctrl: pin gpio0-3 already requested by 20056000.i2c; cannot claim for 10218000.rksdmmc
[    2.190230] rockchip-pinctrl 20008000.pinctrl: pin-3 (10218000.rksdmmc) status -22
[    2.190242] rockchip-pinctrl 20008000.pinctrl: could not request pin 3 on device rockchip-pinctrl
[    1.064171] rockchip-pinctrl 20008000.pinctrl: pin gpio2-20 already requested by 2005a000.i2c; cannot claim for 2008c000.eth

这样就可以看的到gpio0-3 already requested by 20056000.i2c
               gpio2-20 already requested by 2005a000.i2c
               
然后改一下dts就可以               
```
11、mmc驱动扫描接口一般指有三个emmc节点接flash sdmmc节点接tf卡 sdio节点接wifi 其中sdmmc和sdio一样可以用的，当没有tf卡时，wifi经常用sdmmc
```
确定wifi是哪个mmc接口, 30000000 30010000 30020000一共有三个
dwmmc_rockchip 30010000.rksdmmc: dw_mci_init_slot: fmin=200000, fmax=37500000 [mmc2]
mmc2: new high speed SDIO card at address 0001

dmesg |grep 30010000 就可以确认

```

12、PCM
```
最好用逻辑分析仪抓波形
复现问题之前运行hcidump -w xxx.cfa &
复现问题提供xxx.cfa
用逻辑分析仪抓一下PCM_IN PCM_OUT PCM_SYNC PCM_CLK的波形

蓝牙sbc推送数据接口是1.5M的串口
```
13、android 命令连接wifi
```
svc wifi enable
svc wifi disable
在/data/misc/wifi/wpa_supplicant.conf添加
network={
ssid="*******"     #表示wifi热点名
psk="*******"      #表示密码
key_mgmt=WPA-PSK   #加密方式
#key_mgmt-NONE     不加密
}
未启动
wpa_supplicant  -iwlan0  -Dnl80211 -c/data/misc/wifi/wpa_supplicant.conf
svc wifi enable
adb reboot
已启动
wpa_cli reconfigure
wpa_cli reconnect

没有加密或者wep或者使用指令，没有办法，一般都是要使用wpa的使用以上该改法
iwlist scanning | grep ESSID
iw dev wlan0 scan |grep SSID
iw dev wlan0 connect "HUAWEI P10" key 0:3143531435

14、wifi编译驱动
编译为模块
CONFIG_WIFI_BUILD_MODULE=y
CONFIG_RTL8188FU=m
编译入内核
CONFIG_WIFI_BUILD_MODULE=n
CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP=y
CONFIG_RTL8188FU=y

```
15、wifi config.txt配置
```
adb push config.txt /system/etc/firmware/
txglom_mode=0
dhd_slpauto=0
kso_enable=0
```
16、编译modules
```
cd kernel
make ARCH=arm64 CONFIG_RTL8821AU=m -C ./ M=./drivers/net/wireless/rockchip_wlan/rtl8812au modules

make ARCH=arm64 CONFIG_AP6XXX=m -C ./ M=./drivers/net/wireless/rockchip_wlan/rkwifi  modules
```
17、getConnectionState
```
不能用BluetoothAdapter.java的getConnectionState去获取手机的连接状态，
要用BluetoothA2dpSink 下面的api去获取。
```

18、PCM声音调试(pclk和sclk)
```
最好用逻辑分析仪抓波形

a:确定sco链路建立，蓝牙进入sniff mode可以很好体现，抓sniff可以看到链路建立，
也可以用ellisys空中看看有没有，有嘈杂声音肯定就是有数据的了

b:确认sync clk 和pclk由声卡(dts配置)提供还是模组提供，谁作master，断开电阻测试
不能两边都不给clk也不能两边都给clk,必须是一边设置为主另一边设置为从

c:确认声卡(dts配置)clk是否匹配，比如两边设置匹配为 512k 8k或者两边设置匹配为256k 8k 或者512k 16k 都行，
但是两边要沟通好，如果对不上那声音就会嗡嗡嗡什么的都有

d:确认两个sync clk之间的clk数量的要求，比如有16个clk，可以规定 2个slot  8个bit 也可以规定1个slot 32个bit,至于哪里是有效数据，
哪里填充这个就要进一步看配置，比如前8bit是数据后8bit是填充或者前13bit是数据后5bit填充

e:目前8723D正常的config是默认的特别是F8~F9的配置就是没有，就是默认为0，所以很多不用改动的，换句话说就是我默认为0，主控端调试好就行

f:按照config的大端，是正常顺序,包括在reganalyzer上的分析

解决办法（避免声卡纠纷）：首先测量PCM OUT的数据，发现没有信号，很可能是负载有问题，
先将pcm out in sync clk clk断开(断开电阻)，然后将pcm in out 短接，蓝牙耳机或者蓝牙音响自己说话自己听（不是回音），
然后再测量断开的sync clk和clk引脚两端，是哪一端有clk输出，确认哪一边作Master

```
19、wifi断线
```
WIFI断线，得先确认RF指标是OK， 26M频偏 32.768KHZ 波形和电压峰峰值。先找模组代理商做指标测试
板子在其它环境可以正常连接吗， 用WIFI分析仪APK扫描一下周围的环境。 只有一台或概率性有问题建议让代理商再做一下RF测试。让模组代理商到现场去录一下连接的封包sniffer。
```
20、查看wifi/蓝牙驱动版本
```
realtek:  cat  include/rtw_version.h
broadcom: cat  include/epivers.h

realtek:
grep 20170109 -nr
code/libbt-vendor/uart/src/hardware.c:30:#define RTKBT_RELEASE_NAME "20170109_TV_ANDROID_7.x"
code/libbt-vendor/uart/src/bt_vendor_rtk.c:29:#define RTKBT_RELEASE_NAME "20170109_TV_ANDROID_7.x"
code/libbt-vendor/usb/src/bt_vendor_rtk.c:28:#define RTKBT_RELEASE_NAME "20170109_TV_ANDROID_7.x"
rtkbt.mk:1:# RELEASE NAME: 20170109_TV_ANDROID_7.x
```
21、le scan code位置
```
jni_app/Bluetooth/src/com/android/bluetooth/gatt/ScanManager.java
```

22、hw_lpm_enable

23、AP6236 无法连接BLE设备
```
ap6236 默认sdk用不了ble，200d返回的连接参数与sdk不符，不支持le enhance connect，会pageing timeout
参考redmine:231381

```

24、overlay具有重写的作用，但不具备覆盖的作用，所以配置的config.xml一定要确认packages和device overlay
```
默认打开wifi
device/rockchip/common/overlay/frameworks/base/packages/SettingsProvider/res/values/defaults.xml
<bool name="def_wifi_display_on">true</bool>
<bool name="def_wifi_on">true</bool>
```
25、GKI(例如p_msg->hdr.event = BTA_DM_API_SET_NAME_EVT)
```
** Function         bta_sys_sendmsg
**
** Description      Send a GKI message to BTA.  This function is designed to
**                  optimize sending of messages to BTA.  It is called by BTA
**                  API functions and call-in functions.
** Returns          void
```
26、蓝牙串口的锅
```
非常神奇版本或者非常神奇硬件
我们的串口是一个大坑，波特率是非常不准，所以115200 1M 1.5M 2M 都要试一下

diff --git a/bluetooth/libbt/src/userial_vendor.c b/bluetooth/libbt/src/userial_vendor.c
index 6fc9e58..a0823c7 100755
--- a/bluetooth/libbt/src/userial_vendor.c
+++ b/bluetooth/libbt/src/userial_vendor.c
@@ -252,7 +252,7 @@ int userial_vendor_open(tUSERIAL_CFG *p_cfg)

     tcgetattr(vnd_userial.fd, &vnd_userial.termios);
     cfmakeraw(&vnd_userial.termios);
-    vnd_userial.termios.c_cflag |= (CRTSCTS | stop_bits);
+    vnd_userial.termios.c_cflag |=stop_bits;
     tcsetattr(vnd_userial.fd, TCSANOW, &vnd_userial.termios);
     tcflush(vnd_userial.fd, TCIOFLUSH);

编译后将CTS RTS 接地，115200 1M 1.5M 2M 都要试一下，试一下，恒大的问题就是接地115200不行，1.5M可以，是串口的锅

博通回复默认打开流控，不能修改，至于host关流控还没有问题，说明模组忙的时候不多，host忙的时候比较多，所以可以使用这种方法，
RTK接的3线的，正常模组的RTS直接接地，只接了HOST的RTS，那这种解法相当于去掉host流控和HOST RTS接地，这个可以

```
27、pmu 32.768k选择
```
比如PMU rk818
        wireless-bluetooth {
                compatible = "bluetooth-platdata";
                clocks = <&rk818 1>;        // pmu 32.768k 这个要加上
                clock-names = "ext_clock";  // pmu 32.768k 这个要加上
                //wifi-bt-power-toggle;
                uart_rts_gpios = <&gpio2 19 GPIO_ACTIVE_LOW>; /* GPIO2_C3 */

```
28、heartbeat
```
fw没打开heartbeat，上层打开就会心跳计数异常退出
fw打开 上层也打开 会出现长时间概率性断开回连
fw打开fw 上层没有打开 会出现连上反复回连
请联系rtk在config关掉heartbeat，一般只有tv的fw才会有带这个mesh的功能
```
29、查看mmc0 mmc1 mmc2 clock是否配的好
```
cat /d/mmc0/ios
clock:          125000000 Hz
vdd:            23 (3.5 ~ 3.6 V)
bus mode:       2 (push-pull)
chip select:    0 (don't care)
power mode:     2 (on)
bus width:      3 (8 bits)
timing spec:    8 (mmc high-speed SDR200)
signal voltage: 0 (1.80 V)
```
30、特别是8.1的系统蓝牙传文件问题
```
不小心点了传不了的设备，然后再点能传的设备就传不了，我们系统的bug，参考bttransamefile.patch或者psm的那个patch
```
31、双wifi的问题，一个作sta，另一个作ap，有什么问题先使用dual-wifi补丁，还不行就更换wifi驱动

32、蓝牙休眠问题，逻辑分析仪抓博通wake BT引脚，CTS引脚
```
RTK休眠（怎么休眠还得fw来改方式）
1. Non-link mode
1) 放6s 之后就会自动进入LPS。
2) Page Scan、Inquiry Scan、LE Adv、LE Scan 这四个状态下的interval 不能小于0x80。
2. Link mode
1) Sniff 、Page Scan、Inquiry Scan、LE Adv、LE Scan 这四个状态下的interval 不能小于
0x80。
2) 两条Link 不能够进入LPS。
3) 有eSCO、SCO 不会进入LPS。
4) 先进入Sniff Mode 才能进入LPS，如果Sniff Mode 进不去就不会进LPS，Sniff 参数
建议: Nsniff attempt 设置为大于1 的值(Sniff Mode Command)。

博通休眠（怎么休眠还得fw来改方式）

蓝牙休眠是由FW主导的，不是你host，所以下的0xfc27命令才是模组相关休眠的参数，包括低电平有效还是高电平有效，
进入休眠时会不会告诉host这些，或者是模式，可以看到
static bt_lpm_param_t lpm_param =
{
    LPM_SLEEP_MODE,
    LPM_IDLE_THRESHOLD,
    LPM_HC_IDLE_THRESHOLD,
.....
uint8_t hw_lpm_enable(uint8_t turn_on)
这个函数在博通的hardware，有默认的LPM模式，host的控制在RFKILL，包括proc/bluetooth/sleep节点

首先wake BT全程必须保持高电平，否则会不断重启蓝牙（如果是低电平有效的话，除非你关掉LPM）,不断唤醒的话和0XFC27 fw有关
HOST进入休眠RTS拉高，停止传输，退出休眠拉低，再次进行传输，这些都是host的行为，关键还是0xfc27的命令
#define HCI_VSC_WRITE_SLEEP_MODE                0xFC27

/* BT_WAKE Polarity - 0=Active Low, 1= Active High */
#ifndef LPM_BT_WAKE_POLARITY
#define LPM_BT_WAKE_POLARITY            1    /* maguro */
#endif

/* HOST_WAKE Polarity - 0=Active Low, 1= Active High */
#ifndef LPM_HOST_WAKE_POLARITY
#define LPM_HOST_WAKE_POLARITY 1 /* maguro */
#endif

总之不管是极性怎么样，先断开负载，wake bt就测试host的脚  bt wake host就测试bt的脚，
一直直线突然一定会有像心脏一样的唤醒的脉冲，没有就有问题
```
33、usb底层驱动下载android文件系统得fw得方法是通过request_firmware函数

34、蓝牙串口的锅-换模组流控稳定RTS先拉高100ms再拉低
```
#if defined(CONFIG_AP6210) || defined(CONFIG_AP6335)
            gpio_direction_output(rts->io, rts->enable);
            msleep(100);
            gpio_direction_output(rts->io, !rts->enable);
        }
#endif
当开启time out有问题的时候，就需要怀疑流控有问题，就要把这个宏重新自己测试，比如6255也遇到这个问题了
```
35、换模组有时候打的开wifi，有时候打不开，WIFI打开蓝牙才能打开，蓝牙有时后又打不开
```
这个换模组的时候，虽然驱动不用换，但是kernel的配置是需要重新设置的（如果不换就会产生这个问题，应用在驱动和RFKILL配置不对）

也有可能wifi DMA sdio通信出现问题，特别是这种换模块的
dwmmc_rockchip ff500000.rksdmmc: dw_mci_submit_data_dma: fall back to PIO mode for current transfer

wifi驱动主要看mmc 和 使用mmc的wifi驱动 ，其中一个有问题都会不行，一般问题会出在mmc上面，接口用不了
在.config上面配置
CONFIG_MMC_DW_IDMAC = n
```
37、蓝牙不同版本的处理，特别是8.1之后
```
find ./ -name "*conf*"
find ./ -name "*include*"
可以找到配置，主要在hardware 和system/bt
8.1关于log上过滤会多出另一条蓝牙hardware进程，android.hardware.bluetooth@1.0-impl: BluetoothHci::initialize()
要找到它
```
38、AP6330是26M的晶振,AP6255是37.4M的晶振

39、cfa log上进行cmd (opcode group) 分类，是一个非常好的进阶和选择

40、io-domains供电问题，域电压是由PMU或者外部提供，不是由cpu提供，cpu上配置pmu和自己的寄存器匹配域电压，模组上不用配置，给多少就是多少
```
看一下rk808的接线，就一目了然，就是配置输出电压而已，已经接好了的
IO域电压，模组使能引脚和sdio或者uart不在同一个域，或者sdio和uart两端IO电压不一致
-               vccio4-supply = <&rk805_ldo1_reg>;
+               vccio4-supply = <&rk805_dcdc4_reg>;
                vccio5-supply = <&rk805_dcdc4_reg>;
-               sdio_vref = <1800>;
+               sdio_vref = <3300>;
                WIFI,poweren_gpio = <&gpio1 GPIO_C2 GPIO_ACTIVE_HIGH>;
                
                rk805_dcdc4_reg: regulator@3 {
                        regulator-name = "vcc_io";
                        regulator-min-microvolt = <3300000>;
```
41、AP6398S 对硬件要求很高， 给32.768KHZ 放大在100ms内不能角度，如果PMU提供RTC可以实测一下， 可断开外部从RTC芯片飞线过验证看。

42、simple pairing
```
simple pairing mode关闭
第一，去问link key，问不到的话就问pin code

simple pairing mode打开
第一，去问link key，问不到的话就生成link key
```
43、蓝牙wifi以太网抓包
```
hcidump -w xxx.cfa &(android的没有工具看前面模板改)
tcpdump -i eth0 -s 0 -w /data/xxx.pcap &
tcpdump -i wlan0 -s 0 -w /data/xxx.pcap &
最好将抓包的进程关掉再将log提供，不然可能会有错误
```

44、回连问题
```
以前我们有看到经常的simple paring 还有code request 连接 或者是le link key连接  各种各样的安全方式都有
但是总是离不开两个东西，一：地址  二：key
回连不上，就是这两个东西改了，或者模组下的fw被改了
蓝牙是两个设备连接的，所以地址和key是成对存在，谁改了都不行
说说地址：
特别是le地址和br/edr地址，理论上是有两个的，正常来说，看模组的设置来说，只有一个地方改地址，剩下一个给le addr用的只有set random addr这条指令
单从snoop是看不到本地的le addr，空中包就可以看到了，所以：我们默认，没有下random addr指令，le地址就是和br/edr地址一致
ble回连不上，原因经常有两个
1、下发了random addr指令，导致每次重启le addr会变，对端保存不认识你，自然回连不上
2、模组addr变了，比如ota升级，恢复出厂设置，一样回连不上，想要回连就必须保存地址不变
3、bt_cnfig.conf被删了，上面保存着连接的密码，没有自然回连不上
4、fw被换了，模组出问题了，比如天线参数，设备运行等。。这个是必须要确定

br/edr回连不上
1、模组addr变了，比如ota升级，恢复出厂设置，一样回连不上，想要回连就必须保存地址不变
2、bt_cnfig.conf被删了，上面保存着连接的密码，没有自然回连不上
3、fw被换了，模组出问题了，比如天线参数，设备运行等。。这个是必须要确定

可参考蓝牙地址.md
```
45、wifi扫不到AP,8.0之前可以将CONFIG_VTS_SUPPORT配置关掉
```
--- a/drivers/net/wireless/rockchip_wlan/rkwifi/bcmdhd/Makefile
+++ b/drivers/net/wireless/rockchip_wlan/rkwifi/bcmdhd/Makefile
-CONFIG_VTS_SUPPORT := y
+CONFIG_VTS_SUPPORT := n
```
46、关于带宽
```
带宽是无线物理属性，频带宽度（载波能力）
蓝牙BR/EDR  2.4G  79个通道  1M带宽   
调制有DM1 DM3 DM5  有带M字的就是FEC2/3(相当于传3次相同的东西) DH1 DH3 DH5 没有FEC 传的快 
最大3DH5一般是2M小b最快了，传命令一般是DM1几十K小b  传数据一般是3DH5(比如a2dp数据)一般是1.多M小b吞吐

蓝牙BLE     2.4G  40个通道  2M带宽    1M PHY 和2M PHY都是几百K小b吞吐


WIFI 802.11a/b/g  2.4G   20M带宽  一般13个通道（不同国家不同，可能增加或减少通道）  一般几十M小b吞吐

WIFI 802.11a/b/g  /n/ac  2.4G/5G  20M/40M带宽  一般13个通道，还有5G通道（iwlist wlan0 channel可以查看，
通道可以通过国家码在wifi驱动设置）    一般100M小b以上吞吐，5G一般几百M小b吞吐         


WIFI比蓝牙带宽大，传的多，蓝牙主要专注于功耗
```
46、确认用的32位还是64位的.so
```
，如果是64会先找lib64，get module的函数就会有
#if defined(__LP64__)
#define HAL_LIBRARY_PATH1 "/system/lib64/hw"
#define HAL_LIBRARY_PATH2 "/vendor/lib64/hw"
#define HAL_LIBRARY_PATH3 "/odm/lib64/hw"
实例就是32位
getprop |grep ro.product.cpu.abilist
[ro.product.cpu.abilist]: [armeabi-v7a,armeabi]
[ro.product.cpu.abilist32]: [armeabi-v7a,armeabi]
[ro.product.cpu.abilist64]: []
```
47、复用关系快速确定
```
这段可以检查包括复用关系和控制IO进行导通性测试
find /d/ -name "*pinmux*"
cat pinmux-pins
pin 97 (gpio3-1): 30010000.rksdmmc (GPIO UNCLAIMED) function sdio-1 group sdio1-cmd
echo 97 > /sys/class/gpio/export
echo 97 > /sys/class/gpio/gpio97/direction
echo 1 >/sys/class/gpio/gpio97/value

上面一种方法有点局限性，有时侯软件可能显示正常，但是实际不是如此
IO指令快速方法
先找到引脚是哪个，比如3 29
GPIO3?[?]，
29/8=3余5 
0就是A 1就是B 2就是C 3就是D 一共也只有32（0~31）只分组脚
3=D 余5 就直接填 ，3 8 就是 GPIO3B[0]  所以余数可以直接填
所以就是GPIO3D[5]，将这个“GPIO3D[5]”放到datasheet上面查找，一下子就能找到，然后用reganalyzer工具立马可以分析出
```
48、路径
```
find ./ -name "*vendor*"
find ./ -name "*bluetooth*"
Bluetooth.apk
```
49、蓝牙类型修改
```
device/rockchip/common/bluetooth/bdroid_buildcfg.h
http://bluetooth-pentest.narod.ru/software/bluetooth_class_of_device-service_generator.html
```
50、关于休眠出现问题
```
确认模块在休眠时的控制IO电压 电源IO电压 还有有CLK在休眠时与唤醒之后的状态有哪些不同

rockchip-suspend节点修改唤醒功能
PMU 配置各个域regulators 修改休眠供电问题
```
51、android10.0跑进去hw init就死掉
```
--- a/src/upio.c
+++ b/src/upio.c
 #ifndef PROC_BTWRITE_TIMER_TIMEOUT_MS
-#define PROC_BTWRITE_TIMER_TIMEOUT_MS   8000
+#define PROC_BTWRITE_TIMER_TIMEOUT_MS   0
 #endif
```
52、反编译
```
#01 pc 0000000000005950  /vendor/lib64/libbt-vendor.so (upio_set+856) (BuildId: ffd0371b5ff24da2f3eedb08b584ee56)
#02 pc 00000000000031d0  /vendor/lib64/libbt-vendor.so (op+280) (BuildId: ffd0371b5ff24da2f3eedb08b584ee56)
发现错误，这里打印执行文件错误位置，一个执行文件就一个buildid
prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-readelf -a ~/poco/libbt-vendor.so > ~/poco/readelf.txt  可以查看buildid
prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-objdump -dx ~/poco/libbt-vendor.so > ~/poco/objdump.txt  可以查看错误位置地址5950
5950:       940001b4        bl      6020 <timer_settime@plt>
错误就是timer_settime
或prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-addr2line 5950 -e ~/poco/libbt-vendor.so -f -C -s  直接查看位置
找到if (timer_settime(lpm_proc_cb.timer_id, 0, &ts, 0) == 0) {
这个方法就是用来找代码位置的
```
53、有关ble app开发出现问题
```
客户开发BLE APP须自行查找问题，平台是google上更新标准接口的，可以安装Nrf connect测试发送接收，平台问题以nrf connect为准
```
54、wifi fw下载
```
第一个函数是dhd_update_fw_nv_path，第二个函数是dhd_bus_download_firmware
/* try to download image and nvram to the dongle */
	if  (dhd->pub.busstate == DHD_BUS_DOWN && dhd_update_fw_nv_path(dhd)) {
		DHD_INFO(("%s download fw %s, nv %s, conf %s\n",
			__FUNCTION__, dhd->fw_path, dhd->nv_path, dhd->conf_path));
		ret = dhd_bus_download_firmware(dhd->pub.bus, dhd->pub.osh,
  
  wl_android_priv_cmd   
  #define CMD_SETFWPATH		"SETFWPATH"

  默认是rfkill的type和wifi的设备id来匹配
  p2p或者ap下载是上层通过SETFWPATH的cmd控制下载p2p fw
  比如：
  ./etc/firmware/fw_bcm43455c0_ag_p2p.bin
  ./etc/firmware/fw_bcm43455c0_ag_apsta.bin
  ./etc/firmware/fw_bcm43455c0_ag.bin
```
55、蓝牙profile路径
```
device/rockchip/common/overlay/packages/apps/Bluetooth/res/values/config.xml
packages/apps/Bluetooth/res/values/config.xml
overlay 单项覆盖，没有立项则不会抹掉
```
56、8250串口打开打印
```
--- a/drivers/tty/serial/8250/8250.h
+++ b/drivers/tty/serial/8250/8250.h
@@ -219,7 +219,7 @@ static inline int serial_index(struct uart_port *port)
-#if 0
+#if 1
 #define DEBUG_INTR(fmt...)     printk(fmt)
diff --git a/drivers/tty/serial/8250/8250_port.c b/drivers/tty/serial/8250/8250_port.c
index 14665c0..5f1739a 100644
--- a/drivers/tty/serial/8250/8250_port.c
+++ b/drivers/tty/serial/8250/8250_port.c
@@ -46,7 +46,7 @@
-#if 0
+#if 1
 #define DEBUG_AUTOCONF(fmt...) printk(fmt)
```
57、wifi长时间休眠断线
```
系统休眠后，wifi没有数据传输的时候（数据传输不确定性），wifi休眠长时间没有数据传输肯定会断开的
```
58、蓝牙播放出现怪异的声音
```
确认本地播放，播放声音怪异是串口波特率和流控的问题
```
59、关于WIFI开启使能脚延时的问题
```
没有，这个东西，就是热插拔，wifi上电的瞬间，产生中断，wifi就相当于是一个SD卡，然后立马就去读取，很大可能会失败，sdmmc默认都有card-detect-delay进行消抖，sdio很少会失败，但是RTK的模组经常上电不稳定，需要消抖，card-detect-delay = <1200>，延时1.2s为实例
--- a/arch/arm64/boot/dts/rockchip/rk3368-r88.dts
+++ b/arch/arm64/boot/dts/rockchip/rk3368-r88.dts
@@ -448,6 +448,7 @@
        pinctrl-0 = <&sdio0_bus4 &sdio0_cmd &sdio0_clk>;
        sd-uhs-sdr104;
        supports-sdio;
+       card-detect-delay = <1200>;
        status = "okay";
 };

```

