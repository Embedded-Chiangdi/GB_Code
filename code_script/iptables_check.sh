#!/bin/bash
iptables -t nat -nvL | grep 8061 > /dev/null 
if [ $? == 1 ];then
    iptables -t nat -A PREROUTING -p tcp --dport 80 -m mark --mark 0x01 -j DNAT --to-destination 10.1.0.1:8061
fi
iptables -t nat -nvL | grep 8043 > /dev/null 
if [ $? == 1 ];then
    iptables -t nat -A PREROUTING -p tcp --dport 443 -m mark --mark 0x01 -j DNAT --to-destination 10.1.0.1:8043
fi