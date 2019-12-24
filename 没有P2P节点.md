```
01-21 16:50:49.604 1617 1617 E wpa_supplicant: Could not read interface p2p0 flags: No such device
01-21 16:50:49.605 1617 1617 I wpa_supplicant: nl80211: Driver does not support authentication/association or connect commands
```

特别是RTK的驱动
```
应该是p2p0 接口没创建，上层需要p2p0 接口，否则WIFI启动不了。
diff --git a/Makefile b/Makefile
index 4847456..41387fc 100755
--- a/Makefile
+++ b/Makefile
@ -92,7 +92,7 @ CONFIG_MP_VHT_HW_TX_MODE = n ###################### Platform Related #######################
#########rudolph add
CONFIG_PLATFORM_RK3399 =n
-CONFIG_PLATFORM_I386_PC = y
+CONFIG_PLATFORM_I386_PC = n
CONFIG_PLATFORM_ANDROID_X86 = n
CONFIG_PLATFORM_ANDROID_INTEL_X86 = n
CONFIG_PLATFORM_JB_X86 = n
@ -117,7 +117,7 @ CONFIG_PLATFORM_ARM_TCC8920_JB42 = n
CONFIG_PLATFORM_ARM_TCC8930_JB42 = n
CONFIG_PLATFORM_ARM_RK2818 = n
CONFIG_PLATFORM_ARM_RK3066 = n
-CONFIG_PLATFORM_ARM_RK3188 = n
+CONFIG_PLATFORM_ARM_RK3188 = y
CONFIG_PLATFORM_ARM_URBETTER = n
CONFIG_PLATFORM_ARM_TI_PANDA = n
CONFIG_PLATFORM_MIPS_JZ4760 = n
```
