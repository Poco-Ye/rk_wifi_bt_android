1. bluedroid
(1)add: #define BTA_AV_SINK_INCLUDED TRUE
        #define USE_AUDIO_TRACK TRUE
   to files
      device/rockchip/common/bluetooth/bdroid_buildcfg.h
      device/rockchip/px3/bluetooth/bdroid_buildcfg.h



(2)apply sinkAndsrc1106.patch in system/bt/

and then:
mmm system/bt/ -j8

2. Bluetooth app
device/rockchip/common/overlay/packages/apps/Bluetooth/res/values/config.xml
<bool name="profile_supported_a2dp_sink">true</bool>
<bool name="profile_supported_avrcp_controller">true</bool>

and then:
mmm packages/apps/Bluetooth/  -j8 

