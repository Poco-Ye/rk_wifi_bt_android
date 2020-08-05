```
ping -I eth0 www.baid.com
ping -I wlan0 www.baidu.com
ip ru show table eth0

07-24 03:34:26.090   429   537 D WifiNetworkFactory: evalRequest
07-24 06:00:35.946   428   538 D WifiNetworkFactory:  n.requests = true
07-24 06:00:35.946   428   538 D WifiNetworkFactory:  n.score = 70
07-24 06:00:35.946   428   538 D WifiNetworkFactory:  mScore = 80
07-24 06:00:35.946   428   538 D WifiNetworkFactory:  n.factorySerialNumber = -1
07-24 06:00:35.946   428   538 D WifiNetworkFactory:  mSerialNumber = 4
07-24 06:00:35.946   428   538 D WifiNetworkFactory:   done
07-24 06:01:05.873   428   541 D ConnectivityService: handleLingerComplete for NetworkAgentInfo [WIFI () - 103]
07-24 06:01:58.721   428  1119 D ConnectivityService: requestNetwork for uid/pid:1000/751 NetworkRequest [ TRACK_DEFAULT id=57, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED Uid: 1000] ]
07-24 06:01:58.722   428   538 D UntrustedWifiNetworkFactory: got request NetworkRequ


ifconfig wlan0 down
iwconfig wlan0 mode monitor
ifconfig wlan0 up




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


连接隐藏ssid命令：
1. wpa加密
wpa_cli IFNAME=wlan0 add_network
wpa_cli IFNAME=wlan0 set_network 0 ssid \"ASUS_AP1\" 
wpa_cli IFNAME=wlan0 set_network 0 key_mgmt WPA-PSK
wpa_cli IFNAME=wlan0 set_network 0 psk \"66666666\" 
wpa_cli IFNAME=wlan0 set_network 0 priority 0
wpa_cli IFNAME=wlan0 set_network 0 scan_ssid 1
wpa_cli IFNAME=wlan0 enable_network 0
wpa_cli save_config

2. wep加密
wpa_cli IFNAME=wlan0 add_network
wpa_cli IFNAME=wlan0 set_network 0 ssid \"ASUS_AP1\" 
wpa_cli IFNAME=wlan0 set_network 0 key_mgmt NONE
wpa_cli IFNAME=wlan0 set_network 0 auth_alg OPEN SHARED
wpa_cli IFNAME=wlan0 set_network 0 wep_key0 \"66666666\" 
wpa_cli IFNAME=wlan0 set_network 0 wep_tx_keyidx 0
wpa_cli IFNAME=wlan0 set_network 0 priority 0
wpa_cli IFNAME=wlan0 set_network 0 scan_ssid 1
wpa_cli IFNAME=wlan0 enable_network 0
wpa_cli save_config

3. 无加密
wpa_cli IFNAME=wlan0 add_network
wpa_cli IFNAME=wlan0 set_network 0 ssid \"ASUS_AP1\" 
wpa_cli IFNAME=wlan0 set_network 0 key_mgmt NONE
wpa_cli IFNAME=wlan0 set_network 0 priority 0
wpa_cli IFNAME=wlan0 set_network 0 scan_ssid 1
wpa_cli IFNAME=wlan0 enable_network 0
wpa_cli save_config


cat /proc/net/rtl88x2cs/wlan0/survey_info
wpa_cli -iwlan0 scan/scan_r
wpa_cli -iwlan0 log_level debug & logcat -s wpa_supplicat




ifconfig eth0 up
ifconfig eth0 192.168.1.100 broadcast 192.168.1.255 netmask 255.255.255.0 up
单网卡添加多个IP地址
ifconfig eth0:0 192.168.1.100 netmask 255.255.255.0 up
ifconfig eth0:1 192.168.2.100 netmask 255.255.255.0 up
若转换不了域名  主要是域名问题
echo "nameserver 8.8.8.8" > /etc/resolv.conf
或者
ndc resolver setnetdns eth0 "" 8.8.8.8

用ip route
ip addr add 192.168.1.100/24 dev eth0
ip link set dev eth0 up
echo "nameserver 8.8.8.8" > /etc/resolv.conf或者ndc resolver setnetdns eth0 "" 8.8.8.8 8.8.4.4
ip route add default via 192.168.1.1 dev eth0




```
