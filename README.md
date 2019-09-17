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
三步走
第一步：找mapping
第二步：找group
第三步：dts找引脚
```

2、概率性打不开蓝牙，替换8250驱动，dma打开，博通默认打开流控
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

5、.config方法找代码，这样驱动会好

先找到对应的CONFIG_XXX，再到相应的目录进行grep

或者反过来找，先在module上面找到grep "CONFIG*" -nr  再进行查找.confg 如果没有make menuconfig把Kconfig加入进去.config

define config主要放在arch/arm/configs   












