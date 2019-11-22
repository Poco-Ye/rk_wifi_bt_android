
A2DP上的CID是AVCTP，AVCTP 包括AVRCP

在AVCTP上，你会看到只有command和response，不会再有其它，比较好看，就是一个命令控制

TG就是target的意思，这个是被控制端，不用去区分host还是controller,只需要看L2CAP connection是谁发起谁就是CT 

source（手机）端推送音乐，所以手机是TG,音响是CT也可以手机是CT音响是TG，音响上的按键就是CT触发的一种方式，还有其它触发方式（比如本地突然有闹钟或者其

它提示音控制蓝牙那边不要播放）












