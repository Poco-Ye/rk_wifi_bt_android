1、io命令的例子io -4 -w 0xff7b0004 0x00ff000f   一定要0x 不然会报错

cmd:io -4 -r 0x20088004  cmd:io -4 -l 12 0xff770024

先找mapping  再找group

例子3288

GPIO0 0xff750000

GPIO1 0xff780000

GPIO2 0xff790000

组织列表，首先group第一个开始的就是DR（数据）寄存器，然后是DDR（方向）寄存器

GPIO_SWPORTA_DR 0x0000 W 0x00000000 Port A data register

GPIO_SWPORTA_DDR 0x0004 W 0x00000000 Port A data direction register

这个就是group表 io -4 0xff750000  读的就是引脚的电平  io -4 0xff750004  读的就是引脚的方向



















1、概率性打不开蓝牙，替换8250驱动，dma打开，博通默认打开流控

     assert(false && "Unknown HCI message type");
     
     //assert(false && "Unknown HCI message type");

2、
