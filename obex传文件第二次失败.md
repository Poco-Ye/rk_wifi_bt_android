```
--- a/src/com/android/bluetooth/opp/BluetoothOppTransfer.java
+++ b/src/com/android/bluetooth/opp/BluetoothOppTransfer.java
@@ -160,11 +160,16 @@ public class BluetoothOppTransfer implements BluetoothOppBatch.BluetoothOppBatch
                     SdpOppOpsRecord record =
                             intent.getParcelableExtra(BluetoothDevice.EXTRA_SDP_RECORD);
                     if (record == null) {
+                    mConnectThread =
+                            new SocketConnectThread(mDevice, false, true, 4009);
                         Log.w(TAG, " Invalid SDP , ignoring !!");
-                        return;
+                        //return;
                     }
+                   else
+                   {
                     mConnectThread =
                             new SocketConnectThread(mDevice, false, true, record.getL2capPsm());
+                   }
                     mConnectThread.start();
                     mDevice = null;
                 }

```
