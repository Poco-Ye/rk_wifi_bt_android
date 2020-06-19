
```
Android6.0后为了降低功耗保护电池引入doze模式。当满足一定条件后开启doze模式后会禁止app访问网络。

目前SDK默认都开启doze模式：
device/rockchip/common$ grep config_enableAutoPowerModes . -nr
./overlay/frameworks/base/core/res/res/values/config.xml:230: <bool name="config_enableAutoPowerModes">true</bool>

进入doze模式需要满足以下条件：
1、用户不操作设备一段时间
2、屏幕关闭
3、设备未连接电源充电

当设备进入doze模式后，所有的app网络功能都将被禁用，只允许白名单应用和优先级很高的应用可以访问。
系统默认添加白名单可以修改framework/base/data/etc/platform.xml添加标记为allow-in-power-save的项设置，如：<allow-in-power-save package="com.android.providers.downloads" />

设备在使用过程用户也可以手动增加白名单：设置-->电池-->电池优化中将app设置为未优化，反之设置为优化即doze模式下不允许访问网络。


目前发现2017年9月前发布的SDK doze功能没有开启，默认config_enableAutoPowerModes为false

之后发布的SDK包括Android8.1 overlay中默认都开启doze，config_enableAutoPowerModes为true

带GMS包的也是默认为true

vendor/partner_gms/products/gms_overlay/frameworks/base/core/res/res/values/config.xml:25: <bool name="config_enableAutoPowerModes">true</bool>


不想打开就改成false
<bool name="config_enableAutoPowerModes">false</bool>
```
