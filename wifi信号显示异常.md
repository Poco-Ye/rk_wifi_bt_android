```
diff --git a/drivers/net/wireless/rockchip_wlan/rtl8723bu/include/sta_info.h b/drivers/net/wireless/rockchip_wlan/rtl8723bu/include/sta_info.h
index 25ccf7cee454..7236bc07d285 100755
--- a/drivers/net/wireless/rockchip_wlan/rtl8723bu/include/sta_info.h
+++ b/drivers/net/wireless/rockchip_wlan/rtl8723bu/include/sta_info.h
@@ -103,6 +103,7 @@ struct    stainfo_stats    {
     u64    tx_pkts;
     u64    tx_bytes;
     u64  tx_drops;
+    u32  tx_fail_cnt;
 };

 #ifndef DBG_SESSION_TRACKER
diff --git a/drivers/net/wireless/rockchip_wlan/rtl8723bu/os_dep/linux/ioctl_cfg80211.c b/drivers/net/wireless/rockchip_wlan/rtl8723bu/os_dep/linux/ioctl_cfg80211.c
index 5b180b6055db..6eb3f052516a 100755
--- a/drivers/net/wireless/rockchip_wlan/rtl8723bu/os_dep/linux/ioctl_cfg80211.c
+++ b/drivers/net/wireless/rockchip_wlan/rtl8723bu/os_dep/linux/ioctl_cfg80211.c
@@ -28,6 +28,7 @@
 #define STATION_INFO_TX_BITRATE        BIT(NL80211_STA_INFO_TX_BITRATE)
 #define STATION_INFO_RX_PACKETS        BIT(NL80211_STA_INFO_RX_PACKETS)
 #define STATION_INFO_TX_PACKETS        BIT(NL80211_STA_INFO_TX_PACKETS)
+#define STATION_INFO_TX_FAILED          BIT(NL80211_STA_INFO_TX_FAILED)
 #define STATION_INFO_ASSOC_REQ_IES    0
 #endif /* Linux kernel >= 4.0.0 */

@@ -1370,7 +1371,10 @@ _func_enter_;
                         _rtw_memcpy(padapter->securitypriv.dot118021XGrpKey[param->u.crypt.idx].skey,  param->u.crypt.key,(param->u.crypt.key_len>16 ?16:param->u.crypt.key_len));
                         _rtw_memcpy(padapter->securitypriv.dot118021XGrptxmickey[param->u.crypt.idx].skey,&(param->u.crypt.key[16]),8);
                         _rtw_memcpy(padapter->securitypriv.dot118021XGrprxmickey[param->u.crypt.idx].skey,&(param->u.crypt.key[24]),8);
-                                            padapter->securitypriv.binstallGrpkey = _TRUE;    
+                                            padapter->securitypriv.binstallGrpkey = _TRUE;
+                                if (param->u.crypt.idx < 4) 
+                             _rtw_memcpy(padapter->securitypriv.iv_seq[param->u.crypt.idx], param->u.crypt.seq, 8);
+                    
                         //DEBUG_ERR((" param->u.crypt.key_len=%d\n", param->u.crypt.key_len));
                         DBG_871X(" ~~~~set sta key:groupkey\n");

@@ -1853,6 +1857,9 @@ static int cfg80211_rtw_get_station(struct wiphy *wiphy,
         sinfo->filled |= STATION_INFO_TX_PACKETS;
         sinfo->tx_packets = psta->sta_stats.tx_pkts;

+        sinfo->filled |= STATION_INFO_TX_FAILED;
+        sinfo->tx_failed = psta->sta_stats.tx_fail_cnt;
+
     }

     //for Ad-Hoc/AP mode
```
