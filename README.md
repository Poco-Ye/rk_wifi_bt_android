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

3、
