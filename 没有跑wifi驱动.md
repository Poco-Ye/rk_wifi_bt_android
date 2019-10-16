driver/wireless/rockchip_wlan/rtl8812au/os_dep/linux/usb_intf.c
```
int rockchip_wifi_init_module_rtkwifi(void)
{
#ifdef CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP
    int type = get_wifi_chip_type();
    if (type < WIFI_AP6XXX_SERIES || type == WIFI_ESP8089) return 0;
#endif
    printk("\n");
    printk("=======================================================\n");
    printk("==== Launching Wi-Fi driver! (Powered by Rockchip) ====\n");
    printk("=======================================================\n");
    printk("Realtek 8812AU USB WiFi driver (Powered by Rockchip,Ver %s) init.\n", RTL8192_DRV_VERSION);
    rockchip_wifi_power(1);

    return rtw_drv_entry();
}
```

wifi驱动没有跑是因为前面就被返回了，这个地方真的是可以的，所以dts上wifi type的设置有了两个功能

1、下载patch

2、确保驱动可以跑下去
```
#ifdef CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP
    int type = get_wifi_chip_type();
    if (type < WIFI_AP6XXX_SERIES || type == WIFI_ESP8089) return 0;
#endif
```

第一个是宏CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP

这个是module_init的，这个需要配置
```
#ifdef CONFIG_WIFI_BUILD_MODULE
module_init(rockchip_wifi_init_module_rtkwifi);
module_exit(rockchip_wifi_exit_module_rtkwifi);
#else
#ifdef CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP
late_initcall(rockchip_wifi_init_module_rtkwifi);
module_exit(rockchip_wifi_exit_module_rtkwifi);
#else
EXPORT_SYMBOL(rockchip_wifi_init_module_rtkwifi);
EXPORT_SYMBOL(rockchip_wifi_exit_module_rtkwifi);
#endif
#endif
```
有三种配置

1、所以编译进去内核需要CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTUP =y CONFIG_WIFI_BUILD_MODULE=n

还有dts上面，不然驱动就不会跑
```
        wireless-wlan {
-               wifi_chip_type = "ap6335";
+               wifi_chip_type = "rtl8812au";
```

2、编译进内核手动挂 CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTU =n  CONFIG_WIFI_BUILD_MODULE=n  echo 1 > /sys/class/rkwifi/driver

然后也不编译成为module，这个时候就可以在
drivers/net/wireless/rockchip_wlan/wifi_sys/rkwifi_sys_iface.c
```
#ifdef CONFIG_RKWIFI
        if (type < WIFI_AP6XXX_SERIES) {
                if (enable > 0)
                        ret = rockchip_wifi_init_module_rkwifi();
                else
                        rockchip_wifi_exit_module_rkwifi();
                return ret;
        }
#endif
#ifdef CONFIG_RTL_WIRELESS_SOLUTION
        if (type < WIFI_RTL_SERIES) {
                if (enable > 0)
                        ret = rockchip_wifi_init_module_rtkwifi();
                else
                        rockchip_wifi_exit_module_rtkwifi();
                return ret;

```

会根据WIFI_RTL_SERIES，来加载不同module

就是取中间的枚举判断，就是取中间的枚举判断
```
enum {
    WIFI_RK901,
    WIFI_RK903,
    WIFI_AP6181,
    WIFI_AP6210,
    WIFI_AP6212,
    WIFI_AP6234,
    WIFI_AP6330,
    WIFI_AP6335,
    WIFI_AP6354,
    WIFI_AP6441,
    WIFI_AP6476,
    WIFI_AP6493,
    WIFI_AP6XXX_SERIES,
    WIFI_RTL8188EU,
    WIFI_RTL8192DU,
    WIFI_RTL8723AS,
    WIFI_RTL8723BS,
    WIFI_RTL8723BS_VQ0,
    WIFI_RTL8723CS,
    WIFI_RTL8723DS,
    WIFI_RTL8723BU,
    WIFI_RTL8723AU,
    WIFI_RTL8189ES,
    WIFI_RTL8812AU,
    WIFI_RTL8189FS,
    WIFI_RTL8188FU,
    WIFI_RTL8822BS,
    WIFI_RTL_SERIES,
    WIFI_ESP8089,
    WIFI_SSV6051,
    TYPE_MAX,
};

```

3、编译成模块手动挂 CONFIG_WIFI_BUILD_MODULE=y CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTU =y
```
为啥有时候module也不会加载，dts配置type不对，还是因为CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTU设置了的原因，
前面运行直接返回了
CONFIG_WIFI_LOAD_DRIVER_WHEN_KERNEL_BOOTU有纠错的功能，还有就是让module late init，就是两个功能
最好就是dts配置type设置对，这样下载patch才会正确

```
