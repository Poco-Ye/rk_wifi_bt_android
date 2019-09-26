太多这种问题了每次都要我手动敲不好

```
diff --git a/bt_stack.conf b/bt_stack.conf
index 711fe51..280d4bd 100644
--- a/bt_stack.conf
+++ b/bt_stack.conf
@@ -1,6 +1,6 @@
 # Enable BtSnoop logging function
 # valid value : true, false
-BtSnoopLogOutput=false
+BtSnoopLogOutput=true

 # BtSnoop log output file
 BtSnoopFileName=/sdcard/btsnoop_hci.log
```

```
diff --git a/bt_stack.conf b/bt_stack.conf
index 711fe51..0d62aed 100644
--- a/bt_stack.conf
+++ b/bt_stack.conf
@@ -1,6 +1,6 @@
 # Enable BtSnoop logging function
 # valid value : true, false
-BtSnoopLogOutput=false
+BtSnoopLogOutput=true

 # BtSnoop log output file
 BtSnoopFileName=/sdcard/btsnoop_hci.log
@@ -20,19 +20,19 @@ TraceConf=true
 #   BT_TRACE_LEVEL_EVENT   4    ( Debug messages for events )
 #   BT_TRACE_LEVEL_DEBUG   5    ( Full debug messages )
 #   BT_TRACE_LEVEL_VERBOSE 6    ( Verbose messages ) - Currently supported for TRC_BTAPP only.
-TRC_BTM=2
-TRC_HCI=2
-TRC_L2CAP=2
-TRC_RFCOMM=2
-TRC_OBEX=2
-TRC_AVCT=2
-TRC_AVDT=2
-TRC_AVRC=2
-TRC_AVDT_SCB=2
-TRC_AVDT_CCB=2
-TRC_A2D=2
-TRC_SDP=2
-TRC_GATT=2
-TRC_SMP=2
-TRC_BTAPP=2
-TRC_BTIF=2
+TRC_BTM=6
+TRC_HCI=6
+TRC_L2CAP=6
+TRC_RFCOMM=6
+TRC_OBEX=6
+TRC_AVCT=6
+TRC_AVDT=6
+TRC_AVRC=6
+TRC_AVDT_SCB=6
+TRC_AVDT_CCB=6
+TRC_A2D=6
+TRC_SDP=6
+TRC_GATT=6
+TRC_SMP=6
+TRC_BTAPP=6
+TRC_BTIF=6
```
