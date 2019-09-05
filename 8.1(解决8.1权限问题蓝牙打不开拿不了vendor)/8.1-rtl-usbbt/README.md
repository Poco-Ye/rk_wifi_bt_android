1.usb的fw要放在机器的/system/etc/firmware/ ,把Firmware下面的文件拷贝到/system/etc/firmware/ 

2.libbt-vendor直接替换 hardware/realtek/rtkbt/code/libbt-vendor/

3.linux目前为kernel下面最新的补丁，直接替换

4.bt-usb-selinux.patch为selinux补丁， device/rockchip/common/

5.hardware/realtek/rtkbt/vendor/etc/bluetooth/rtkbt.conf 这个文件里面，要设置 BtDeviceNode=/dev/rtk_btusb

  这个文件是拷贝到/vendor/etc/bluetooth/
