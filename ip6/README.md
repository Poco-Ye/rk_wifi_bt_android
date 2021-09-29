
```
和PC是设置静态IPV6地址吗， 帮忙先录个封包过来。
tcpdump -i eth0 -s 0 -w /data/1.pcap

ifcofig
ip -6 rule
ip -6 route
ip -6 show table eth0
ip -6 show table main
ip -6 show table local



那是不是上层把地址清空了，

setprop log.tag.NativeDaemonConnector D
setprop log.tag.NetworkManagement D
setprop log.tag.NetworkAgentInfo D
setprop log.tag.ConnectivityService D
setprop log.tag.netd D
setprop log.tag.EthernetNetworkFactory D
setprop log.tag.NetworkFactory D
setprop log.tag.NetworkAgent D
setprop log.tag.DnsManager D

logcat -c;logcat > /data/logcat.txt
ping6
看是否上层下命令清清了地址。


```
