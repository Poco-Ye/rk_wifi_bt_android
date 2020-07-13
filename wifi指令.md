```
wpa_cli ifname=wlan0 scan
wpa_cli ifname=wlan0 scan_r

android 命令连接wifi

svc wifi enable
svc wifi disable
在/data/misc/wifi/wpa_supplicant.conf添加
network={
ssid="*******"     #表示wifi热点名
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
```
