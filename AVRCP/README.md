```
A2DP上的CID是AVCTP，AVCTP 包括AVRCP

在AVCTP上，你会看到只有command和response，不会再有其它，比较好看，就是一个命令控制

TG是source CT是sink

经常的需求：
1、sink本地提示音播放暂停source
2、source播放暂停sink本地播放

1、sink 蓝牙播放 audiofocus loss -> sink CT 控制pause source AG 推送 -> sink audiofoucs get again -> sink CT 控制start source AG推送
2、source播放-> handle message蓝牙播放 play -> audiofources request -> sink本地播放器audiofocus loss

audiofocus 才是中断

public void handleMessage(Message message) {
if (DBG) {
Log.d(TAG, " process message: " + message.what);
Log.d(TAG, " audioFocus = " + mAudioFocus);
}
switch (message.what) {
case SRC_STR_START: //收到A2dp start进度条开始播放的时候
case SRC_STR_STOP: //A2dp stop进度条播放完了
case SNK_PLAY:   //进度条在中间暂停后由CT控制重新再播放
case SNK_PAUSE: //进度条在中间由CT暂停
case SRC_PLAY: //进度条在中间由AG播放器恢复播放
case SRC_PAUSE://进度条在中间由AG播放器暂停播放
case DISCONNECT: // 播放着突然断线
case AUDIO_FOCUS_CHANGE: //蓝牙播放的时候突然由其它软件抢占播放
case AudioManager.AUDIOFOCUS_GAIN:  //重新获得播放权
case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK: //失去部分播放权，进入潜水模式，声音变非常小
case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT: //短暂失去播放权，消抖
case AudioManager.AUDIOFOCUS_LOSS://失去播放权


```










