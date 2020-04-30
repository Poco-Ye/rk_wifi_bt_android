```
保证.config是支持USB

CONFIG_USB_NET_DRIVERS=y
CONFIG_RTL_CARDS=y
CONFIG_SND_USB=y
CONFIG_USB_HID=y
CONFIG_USB=y
CONFIG_USB_DEFAULT_PERSIST=y
将新的驱动包的文件放到 /kernel/drivers/bluetooth
drivers/bluetooth/rtk_bt.c
drivers/bluetooth/rtk_bt.h
drivers/bluetooth/rtk_coex.c
drivers/bluetooth/rtk_coex.h
drivers/bluetooth/rtk_misc.c
drivers/bluetooth/rtk_misc.h

diff --git a/drivers/bluetooth/Makefile b/drivers/bluetooth/Makefile
index ba76ca9..479a164 100644
--- a/drivers/bluetooth/Makefile
+++ b/drivers/bluetooth/Makefile
@@ -13,7 +13,7 @@ obj-$(CONFIG_BT_HCIBLUECARD)  += bluecard_cs.o
 obj-$(CONFIG_BT_HCIBTUART)     += btuart_cs.o

 obj-$(CONFIG_BT_HCIBTUSB)      += btusb.o
-obj-$(CONFIG_BT_RTKBTUSB)      += rtk_btusb.o
+obj-m                          += rtk_btusb.o
 obj-$(CONFIG_BT_HCIBTSDIO)     += btsdio.o

 obj-$(CONFIG_BT_INTEL)         += btintel.o
@@ -39,4 +39,6 @@ hci_uart-$(CONFIG_BT_HCIUART_BCM)     += hci_bcm.o
 hci_uart-$(CONFIG_BT_HCIUART_QCA)      += hci_qca.o
 hci_uart-objs                          := $(hci_uart-y)

+rtk_btusb-y = rtk_coex.o rtk_misc.o rtk_bt.o
+
 ccflags-y += -D__CHECK_ENDIAN__

修改后编译
```
