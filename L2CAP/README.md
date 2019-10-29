0405指令下发后 ACL链路连接success之后

就是这条指令Ok之后

后面的ACL链路都是建立在L2CAP之上的

以CID为主 PSM为协议(SDP OBEX A2DP AVRCP RFCOMM HFP)

首先用以CID 0x0001(非PSM)还要其它特殊的CID(0x0007是smp)进行命令式信息交互（infomation request）主要询问支持的协议或者安全

其它普通的CID是PSM连接，都必须先用PSM进行 connect request 获得对端的PMS CID（比如0x0043） CID不是固定的，需要用psm request去拿 

然后，所有的协议管理是由SDP管理的，这个只是一个表，存放协议的版本、厂商、PSM

可以理解为CID 0x0001 去拿到其它CID 

协议的CID是成对出现的，比如SDP ，经常使用之后就会断开丢弃，再继续通信需要再生成一对CID


我们看通信就只看PSM就可以了，有没有request，然后连接上进行通信











