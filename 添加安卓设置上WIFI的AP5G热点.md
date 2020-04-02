wpa_supplicant.conf
```
cat data/misc/wifi/wpa_supplicant.conf
ctrl_interface=/data/misc/wifi/sockets
disable_scan_offload=1
driver_param=use_p2p_group_interface=1p2p_device=1
update_config=1
device_name=rk322x_box
manufacturer=rockchip
model_name=rk322x-box
model_number=rk322x-box
serial_number=P1QRMMGNE3
device_type=10-0050F204-5
config_methods=physical_display virtual_push_button
p2p_no_go_freq=5170-5740
pmf=1
external_sim=1
wowlan_triggers=any
p2p_search_delay=0

network={
        ssid="poco"
        bssid=30:74:96:75:24:a7
        psk="3143531435"
        key_mgmt=WPA-PSK
        id_str="%7B%22creatorUid%22%3A%221000%22%2C%22configKey%22%3A%22%5C%22poco%5C%22WPA_PSK%22%7D"
}

```
hostapd.conf
```
cat /data/misc/wifi/hostapd.conf
interface=wlan0
driver=nl80211
ctrl_interface=/data/misc/wifi/hostapd
ssid=AndroidAP
channel=1
ieee80211n=1
hw_mode=g
ignore_broadcast_ssid=0
wowlan_triggers=any
wpa=2
rsn_pairwise=CCMP
wpa_psk=2a336741dae590f54e1c7924c940559a848840030ee965aaa178023ab490023b
```

```
STA模式
串口命令：
echo 1 > /sys/class/rkwifi/driver 驱动加载
ifconfig wlan0 up 启动网卡
wpa_supplicant -Dnl80211 -c /tmp/wpa_supplicant.config -iwlan0 -B 连接热点。
udhcpc -i wlan0 -b 获取ip地址
模组能够正常连接上wifi热点并获取到ip地址。wpa_supplicant的配置内容可以参考下面。系统在etc目录会有配置文件，只需要修改对应的ssid和密码，就可以直接使用该配置文件。
ctrl_interface=/var/run/wpa_supplicant
ap_scan=1
network={
proto=RSN
key_mgmt=WPA-PSK
pairwise=CCMP TKIP
group=CCMP TKIP
ssid="name"
psk="password"
}

```
```
AP模式
串口命令：
echo 1 > sys/class/rkwifi/driver 驱动加载
ifconfig lo 127.0.0.1 netmask 255.255.255.0;
ifconfig wlan0 192.168.100.1 netmask 255.255.255.0 设置ip地址
dnsmasq -C /etc/dnsmasq.conf 启动dns
hostapd /tmp/hostapd.conf -B 启动ap模式
模组能够正常启动ap 模式。hostapd.conf配置内容参考如下
ctrl_interface=/tmp/hostapd
interface=wlan0
driver=nl80211
ssid="name"
channel=6
hw_mode=g
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase="password"
rsn_pairwise=CCMP

```
上面是熟悉一下，这里是添加5G的血槽，countrycode一般没有设置，这个是有sim卡设置的，正常没有设置，主要看ro.boot.wificountrycode

还有ap高频段5G支持也打开

<bool translatable="false" name="config_wifi_dual_band_support">true</bool>

```
diff --git a/src/com/android/settings/wifi/WifiApDialog.java b/src/com/android/settings/wifi/WifiApDialog.java
index 1316a49..942bdc2 100644
--- a/src/com/android/settings/wifi/WifiApDialog.java
+++ b/src/com/android/settings/wifi/WifiApDialog.java
@@ -135,7 +135,7 @@ public class WifiApDialog extends AlertDialog implements View.OnClickListener,

         ArrayAdapter <CharSequence> channelAdapter;
         String countryCode = mWifiManager.getCountryCode();
-        if (!mWifiManager.isDualBandSupported() || countryCode == null) {
+        if (0) {
             //If no country code, 5GHz AP is forbidden
             Log.i(TAG,(!mWifiManager.isDualBandSupported() ? "Device do not support 5GHz " :"")
                     + (countryCode == null ? " NO country code" :"") +  " forbid 5GHz");
diff --git a/service/java/com/android/server/wifi/util/ApConfigUtil.java b/service/java/com/android/server/wifi/util/ApConfigUtil.java
index 0e12f06..e404709 100644
--- a/service/java/com/android/server/wifi/util/ApConfigUtil.java
+++ b/service/java/com/android/server/wifi/util/ApConfigUtil.java
@@ -33,6 +33,7 @@ public class ApConfigUtil {

     public static final int DEFAULT_AP_BAND = WifiConfiguration.AP_BAND_2GHZ;
     public static final int DEFAULT_AP_CHANNEL = 6;
+    public static final int DEFAULT_AP_CHANNEL_5GHz = 153;

     /* Return code for updateConfiguration. */
     public static final int SUCCESS = 0;
@@ -115,16 +116,22 @@ public class ApConfigUtil {
                                             WifiConfiguration config) {
         /* Use default band and channel for device without HAL. */
         if (!wifiNative.isHalStarted()) {
-            config.apBand = DEFAULT_AP_BAND;
-            config.apChannel = DEFAULT_AP_CHANNEL;
-            return SUCCESS;
+            if (WifiConfiguration.AP_BAND_2GHZ == config.apBand)
+               config.apChannel = DEFAULT_AP_CHANNEL;
+            else if (WifiConfiguration.AP_BAND_5GHZ == config.apBand)
+                config.apChannel = DEFAULT_AP_CHANNEL_5GHz;
+            else {
+               config.apBand = DEFAULT_AP_BAND;
+               config.apChannel = DEFAULT_AP_CHANNEL;
+           }
+           return SUCCESS;
         }

         /* Country code is mandatory for 5GHz band. */
         if (config.apBand == WifiConfiguration.AP_BAND_5GHZ
                 && countryCode == null) {
             Log.e(TAG, "5GHz band is not allowed without country code");
-            return ERROR_GENERIC;
+            //return ERROR_GENERIC;
         }
```
