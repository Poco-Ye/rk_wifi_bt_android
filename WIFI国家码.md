
```
配置SDK device/rockchip/common/BoardConfig.mk

androidboot.wificountrycode=US



上层是可以设置setprop ro.boot.wificountrycode=US 是根据不同语言去设置。


代码上可以搜ro.boot.wificountrycode
wifi通过这个属性来拿



另外AP系列模块设置国家码需要同时配置country_list。

如设置US/CN/JP可以在/vendor/etc/firmware/config.txt中增加以下内容，config.txt文件创建一个，在push进去。
country_list=US:US/988, CN:CN/38, JP:JP/58

欧洲： 德国 DE/7, 法国 FR/5，意大利 IT/4，英国 GB/6，西班牙 ES/4，葡萄牙 PT/4，荷兰 NL/4，瑞士 SZ/0，波兰 PL/4，俄罗斯 RU/13，希腊 GR/4，挪威 NO/4;
亚洲: 韩国 KR/57，新加坡 SG/0，印度 IN/3，以色列 IL/14，沙特阿拉伯 SA/0，阿联酋(迪拜) AE/6；
美洲：加拿大 CA/2，墨西哥 MX/44，巴西 BR/2，阿根廷 AR/0，智利 CL/0；
大洋洲：澳大利亚 AU/6，新西兰 NZ/4；

按照country_list=US:US/988, CN:CN/38, JP:JP/58格式填写到config.txt即可。

配置前：
dmesg | grep country
[ 199.650777] dhd_conf_set_country: set country CN, revision 38
[ 199.838009] WLDEV-INFO) wldev_set_country: Current country CN rev 38
[ 199.864526] wldev_set_country: set country for US as US rev 0

dmesg | grep country
[ 44.781943] dhd_conf_set_country: set country CN, revision 38
[ 44.946887] WLDEV-INFO) wldev_set_country: Current country CN rev 38
[ 44.964031] wldev_set_country: set country for CN as CN rev 0

dmesg | grep country
[ 48.458995] dhd_conf_set_country: set country CN, revision 38
[ 48.686643] WLDEV-INFO) wldev_set_country: Current country CN rev 38
[ 48.712046] wldev_set_country: set country for JP as JP rev 0

配置后:
[17426.115535] dhd_conf_read_country_list: 4 country in list
[17426.330978] dhd_conf_map_country_list: CN/38
[17426.331000] dhd_conf_set_country: set country CN, revision 38
[17426.544912] dhd_conf_map_country_list: JP/58
[17426.544942] WLDEV-INFO) wldev_set_country: Current country CN rev 38
[17426.578062] wldev_set_country: set country for JP as JP rev 58






RTK的
驱动自适应，需要咨询一下原厂，他们应该默认固定在驱动中了，不同过家有不同功率值。这个问原厂比较清楚。


```
