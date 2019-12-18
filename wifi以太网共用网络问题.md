两个wifi模组，一个eth0

wifi一个作sta连网，另一个作ap可以有网络，双wifi

但是类似于电脑连接以太网,电脑打开wifi热点来测试，不行

rk3288 7.1双wifi热点，如何配置使用有线网络.rk3288 双wifi模块 
rtl8821cu（sta）+AP6255（AP），目前使用rtl8821cu连接网络AP6255的AP热点手机连接可以上网，
但是如果断开wifi，使用有线网络，wifi AP无法使用网络

static int cfg80211_netdev_notifier_call(struct notifier_block *nb,
unsigned long state, void *ndev) {

.......
 switch (state) {
  case NETDEV_REGISTER:   // 注册设备
    if ((wdev->iftype  NL80211_IFTYPE_STATION ||
    　　wdev->iftype  NL80211_IFTYPE_P2P_CLIENT ||
    　　wdev->iftype == NL80211_IFTYPE_ADHOC) && !wdev->use_4addr)
   　　dev->priv_flags |= IFF_DONT_BRIDGE;   
  　　break;
 }
.........
} 
当设备为client或者adhoc以及wds时，对应的无线接口是无法加入到桥接中去的，但softap可以加入br0.
所以我建议，eth0 wlan1时走bridge, wlan0 wlan1走NAT。

双wifi时 走nat

eth0 和 wifi ap 桥接就可以






