```
指令043e(req)或0429 (rsp)

有一个坑爹的东西就是你设置的正基的参数设置好了，但是协商就变了，你们的声卡又只支持cvsd，那就不能再协商msbc  
AT+BAC/AT+BCS上位机指令 和+BAC 下位机反馈




diff --git a/system/bt/bta/hf_client/bta_hf_client_at.cc b/system/bt/bta/hf_client/bta_hf_client_at.cc
index 5d8493b..c26a835 100644
--- a/system/bt/bta/hf_client/bta_hf_client_at.cc
+++ b/system/bt/bta/hf_client/bta_hf_client_at.cc
@@ -437,6 +437,7 @@ static void bta_hf_client_handle_bcs(tBTA_HF_CLIENT_CB* client_cb,
   APPL_TRACE_DEBUG("%s: codec: %u sco listen state: %d", __func__, codec,
                    client_cb->sco_state);
   if (codec == BTM_SCO_CODEC_CVSD || codec == BTM_SCO_CODEC_MSBC) {
+    codec == BTM_SCO_CODEC_CVSD;
     client_cb->negotiated_codec = codec;
     bta_hf_client_send_at_bcs(client_cb, codec);
   } else {
@@ -1647,7 +1648,7 @@ void bta_hf_client_send_at_bac(tBTA_HF_CLIENT_CB* client_cb) {

   APPL_TRACE_DEBUG("%s", __func__);

-  buf = "AT+BAC=1,2\r";
+  buf = "AT+BAC=1,1\r";

   bta_hf_client_send_at(client_cb, BTA_HF_CLIENT_AT_BAC, buf, strlen(buf));
 }
 
 
 
 或者直接打这个，这个我还没搞清楚
 #ifndef BTIF_HF_CLIENT_FEATURES
#define BTIF_HF_CLIENT_FEATURES                                                \
  (BTA_HF_CLIENT_FEAT_ECNR | BTA_HF_CLIENT_FEAT_3WAY |                         \
   BTA_HF_CLIENT_FEAT_CLI | BTA_HF_CLIENT_FEAT_VREC | BTA_HF_CLIENT_FEAT_VOL | \
-   BTA_HF_CLIENT_FEAT_ECS | BTA_HF_CLIENT_FEAT_ECC | BTA_HF_CLIENT_FEAT_CODEC)
+   BTA_HF_CLIENT_FEAT_ECS | BTA_HF_CLIENT_FEAT_ECC )
#endif

```
