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

2、概率性打不开蓝牙，替换8250驱动，dma打开，博通默认打开流控，或者文件传输出问题
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

PMU提供DCDC电压（3.3~4.2V）给模组的VBAT  提供LDO 电压（1.8V或者3.3V给VCCIO） 同时也设置CPU IO（串口和sdio）
域电压1.8或者3.3V 还有LPO 32.768K给模组 
sdio_vref = <1800>; //1800mv or 3300mv
如果3288 wifi概率性起不来（312x sdio_vref没有作用），就需要检查一下vccio设置的对不对
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

12、PCM
```
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
```
19、wifi断线
```
WIFI断线，得先确认RF指标是OK， 26M频偏 32.768KHZ 波形和电压峰峰值。先找代理商做指标测试
```
20、查看wifi驱动版本
```
realtek:  cat  include/rtw_version.h
broadcom: cat  include/epivers.h
```
21、le scan code位置
```
jni_app/Bluetooth/src/com/android/bluetooth/gatt/ScanManager.java
```

22、hw_lpm_enable

23、ap6236 默认sdk用不了ble，200d返回的连接参数与sdk不符，不支持le enhance connect

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
