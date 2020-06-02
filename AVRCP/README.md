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

```










