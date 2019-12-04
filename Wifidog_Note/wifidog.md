# Wifidog Note
## Target
拒绝重复造轮子 无意义的摘抄  
# WIFIDOG
## What is wifidog？
什么是WIFIDOG ? 简言之，实现上网认证的程序。
## Captive portal

### Implementation

## code of wifidog analysis

## note for wifidog

# IPTABLES
## what is iptables
**iptables** is rule based command-line firewall and it's pre-installed on most of linux operating system.
## basic command of iptables
some basic command as follow:
```
#checking the status of iptables/firewall.
iptables -L -n -v
iptables -L -n -v --line-numbers
#flushing or deleting ip tables rules
iptables -F
#Adding rules
iptables -A chain_name criteria -j target
```
### example 1 : Analyzing the difference between the DROP and REJECT policies
```
ping -c 3 $host_ip
iptables -A INPUT --protocol icmp --in-interface eth0 -j DROP
ping -c 3 $host_ip
iptables -F
iptables -A INPUT --protocol icmp --in-interface th0 -j REJECT
ping -c 3 $host_ip
```
# Contact 
# Reference
* [Captive portal](https://en.wikipedia.org/wiki/Captive_portal)
* [Wifidog源码分析-初始化阶段](https://www.cnblogs.com/tolimit/p/4221719.html)    
* [Wifidog源码分析-wifidog原理](https://www.cnblogs.com/tolimit/p/4223644.html)    
* [wifidog源码分析-用户连接过程](https://www.cnblogs.com/tolimit/p/4224541.html)  
* [wifidog_source_code_analysis_1](http://www.programmersought.com/article/60631844738/)  
* [wifidog_source_code_analysis_2](http://www.programmersought.com/article/14071844727/)  
* [wifidog_source_code_analysis_3]()  
* [WIFIDOG认证](https://blog.csdn.net/u011034150/article/details/51065811)  
* [WIFIDOG源码分析](https://www.csdndoc.com/article/8985024)  
* [wifidog添加URL白名单](https://blog.csdn.net/liuzheng081/article/details/51770176)  