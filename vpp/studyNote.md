# VPP 学习笔记
## 基础知识
### 桥
A network bridge is a Link Layer device which forwards traffic between networks based on MAC addresses and is therefore also referred to as a Layer 2 device.It makes forwarding decisions based on tables of MAC addresses which it builds by learning what hosts are connected to each network. A software bridge can be used within a Linux host in order to emulate a hardware bridge, for example in virtualization applications for sharing a NIC with one or more virtual NICs.
#### Creating a btidge
manage a  network bridge using the ip tool from iproute2 package.
```s
#create a new bridge and change its state to up 
ip link add name $bridge_name type bridge
ip link set $bridge_name up
#add an interfcae into the bridge, its state must up
ip link set eth0 up
ip link set eth0 master $bridge_name
#show the existing bridges and associated interfaces
bridge link
#remove an interface from a bridge 
ip link set eth0 nomaster
#delete a bridge issue 
ip link delete $bridge_name type  bridge
#assign an ip address 
ip addr add dev bridge_name 172.16.17.1
```
***
manage a network bridge using the legacy brctl tool.
```s
#create a new bridge:
brctl addbr btidge_name
#dele a bridge
brctl delbr bridge_name
#add a device to a bridge fow exaple eth0
brctl addif bridge_name eth0
#show current bridges and what interfaces they are connected to:
brctl show

ip link set dev bridge_name up

```
Attaching an IP address to a bridge device is only necessary if you want to orignate, or receive IP traffic on that interface. If you are merely using your two NICs as a repeater (of sorts) then you shouldn't need an IP address.
#### Ref:
1. [networking:bridge [Wiki]](https://wiki.linuxfoundation.org/networking/bridge)
2. [microHOWTO: Bridge traffic between two or more Ethernet interfaces on Linux](http://www.microhowto.info/howto/bridge_traffic_between_two_or_more_ethernet_interfaces_on_linux.html)
3. [Why do we need an IP address for a bridge?](https://askubuntu.com/questions/407828/why-do-we-need-an-ip-address-for-a-bridge)
4. [Linux Bridge - Part 1](https://hechao.li/2017/12/13/linux-bridge-part1/)
### 路由
In computer networking, a router is a device responsible for forwarding network traffic. When datagrams arrive at a router, the router must determine the best way to route them to their destination.
#### Linux route command
```s
# show route
route -n 
# add route
route add -net 192.168.2.0 netmask 255.255.255.0 dev eth0
# add a default gateway
route add default gw 192.168.1.10
# block a host run
route add -host 192.168.1.19 reject

```
#### Ref
1. [Linux route command](https://www.computerhope.com/unix/route.htm)
2. [An introduction to Linux network routing](https://opensource.com/business/16/8/introduction-linux-network-routing)
3. [7 Linux Route Command Examples (How to Add Route in Linux)](https://www.thegeekstuff.com/2012/04/route-examples/)
4. [Understanding Routing table entry](https://stackoverflow.com/questions/8599424/understanding-routing-table-entry)
5. [route command output](https://stackoverflow.com/questions/36515518/route-command-output)
### NAT
#### Basic
#### Reference
1. (NAT - Network Address Translation)[https://www.karlrupp.net/en/computer/nat_tutorial]
2. ()[]
### VLAN
#### Config VLan
##### Method 1
```s
cp /etc/sysconfig/network-scripts-eth0 /etc/sysconfig/network-scripts-eth0.5
vi /ets/sysconfig/network-scripts/ifcfg-eth0.5

#Replcae follow Items
Device=eth0.5
VLAN=yes


``` 
##### Method 2 
```s
vconfig add eth0 5
ifconfig eth0.5 192.168.1.100 netmask 255.255.255.0 broadcase 192.168.1.255 up

#Get detail information about VLAN interface
cat /proc/net/vlan/eth0.5
#Dele VLAN interface
ifconfig eth0.5
vconfig rem eth0.5
```
##### Method 3
```s
ip link add  link eth0 name eth0.5 type vlan id 5
ip link
ip -d link show eth0.5
ip addr add 192.168.1.200/24 brd 192.168.1.255 dev eth0.5
#Remove Vlan id
ip link set dev eth0.5 up
ip link set dev eth0.5 down 
ip link delete eth0.5
```

#### Reference 
1. (HowTo: Configure Linux Virtual Local Area Network (VLAN))[https://www.cyberciti.biz/tips/howto-configure-linux-virtual-local-area-network-vlan.html]
2. 
### 端口聚合
The Linux bonding driver provides a method for aggregating multiple network interfaces into a single logical “bonded” interface. 
```s
#Querying Bonding Configuration
cat /proc/net/bonding
```
#### Reference
1. [Basics of Ethernet Bonding in Linux](https://www.thegeekdiary.com/basics-of-ethernet-bonding-in-linux/)

### TUN/TAP Interface

### Veth Interface

### ACL

### 流控

## 入门学习目标
VPP本身只是包处理加速框架，后来基于这个框架才构建的用户态网络协议栈。先了解用户态网络协议栈技术。然后再了解VPP向量包处理技术。
## 简述
## 编译&安装
基于Centos7
```shell
#Get the newest version of VPP sources code
git clone https://gerrit.fd.io/r/vpp
#
git clone -b stable/1908 https://github.com/FDio/vpp.git
cd vpp

//Make sure there are no FD.io VPP or DPDK packages
rpm -q vpp
rpm -q DPDK

//Build VPP Dependencies
make install-dep 

//Build VPP Release Version
make build-release

//Building Necessary Packages 
make pkg-rpm
```
Afer packages are built, they will be put in build-root directory.And finaly we can install the package to our system.
``
cd /vpp/buil-root
rpm -ivh *.rpm
``
## VPP应用
### VPP的配置
绑定网口
```s
#Get pci address 
lshw -c network -businfo
lspci -m
```

驱动导入
```
modprobe uio_pci_generic
modprobe igb_uio
```
将获取的PCI网口ID写入startup.conf 文件。
### VPP应用基础
参考连接：[VPP BASSIC](https://wiki.fd.io/view/VPP/Progressive_VPP_Tutorial)  
#### prepare
```
vpp unix {cli-listen /run/vpp/cli-vpp1.sock} api-segment {prefix vpp1}
```
* `api-segment {prefix vpp1}` indicate how to name the files in /dev/shm for our vpp
* `unix {cli-listen /run/vpp/cli-vpp1.sock} ` tells vpp to use a non-default socket file when being addressed by vppctl.

Using vppctl to send commands to vpp
```
vppctl command
vppctl show ver
```

#### Lab1  Create an Interface
Example of how to create a host interface tied to one side of an existing linux veth pair named vpp1, and enable the interface.
```s
#Create a veth interface with one end name vpp1out and the other named vpp1host
ip link add name vpp1out type veth peer name vpp1host
#turn up both ends
ip link set dev vpp1out up
ip link set dev vpp1host up
#Assign an IP address
ip addr add 10.10.1.1/24 dev vpp1host
#Display an IP address 
ip addr show vpp1host

#Create vpp host-interface
create host-interface name vpp1out
    

# Examine Trace of ping 
trace add af-packet-input 10
ping  10.10.1.1
show trace
# Clean trace buffer
clear trace
# Examine arp tables
show ip arp
# show routing table 
show ip fib
```




#### Lab2 
```s
#create memif interface on vpp1
create interface memif id 0 master
#Above command will create an interface on vpp1 memif0/0 using /run/vpp/memif as its socket file.
#set the memif0/0 state to up
set  int state memif0/0 up
#assign the ip address 10.10.2.1/24 to memif0/0
set int ip address memif0/0 10.10.2.1/24
#examint memif0/0 via show commands




#Create memif interface on vpp2
create interface memif id 0 slave
set int state memif0/0 up
set int ip address memif0/0 10.10.2.2/24

```

#### Lab4
```s
#Setup host route
ip route 10.10.2.0/24 via 10.10.1.2
#Confirm ip route
ip route



#Set up route on vpp2
ip route add 10.10.1.0/24 via 10.10.2.1
trace add memif-input 10

#Set up trace on vpp1
trace add

#ping 10.10.2.2. on the host
ping -c 1 10.10.2.2

#Examine the trace on vpp1 and vpp2
show trace
```


# Lab5 

```s
#Initial state
ps -ef | grep vpp | awk '{print $2}'| xargs sudo kill
sudo ip link del dev vpp1host
sudo ip link del dev vpp1vpp2

#Create a veth with one end named vpp1host and the other named vpp1out\
#connect vpp1out to vpp1
#add ip address 10.10.1.1/24 on vpp1host
ip link add name vpp1out type veth peer name vpp1host
ip link set dev vpp1out up
ip link set dev vpp1host up
ip addr add 10.10.1.1/24 dev vpp1host
ip addr show vpp1host

vppctl -s /run/vpp/cli-vpp1.sock
create host-interface name vpp1out
set int state host-vpp1out up
show int
quit

#create  a veth with one end named vpp1vpp2 and the other named vpp2vpp1
#connect vpp1vpp2 to vpp1
#connect vpp2vpp1 to vpp2
ip link add name vpp1vpp2 type veth peer name vpp2vpp1
ip link set dev vpp1vpp2 up
ip link set dev vpp2vpp1 up
vppctl -s /run/vppcli-vpp1.sock
create host-interface name vpp1vpp2
set int state host-vpp1vpp2 up
quit 
vppctl -s /run/vppcli-vpp2.sock
create host-interface name vpp2vpp1
set int state host-vpp2vpp2 up
quit
#Configure Bridge Domain on vpp1
set int l2 bridge host-vpp1out 1
set int l2 bridge host-vpp1vpp2 1
show bridge-domain 1 detail
quit

#Config loopback interface on vpp2
vppctl -s /run/vpp/cli-vpp2.sock
create loopback interface
#loop0
set int ip address loop0 10.10.1.2/24
set int state loop0 up
#Configure Bridge Domain on vpp2

set int l2 bridge loop0 1 bv1
set int l2 bridge host-vpp2vpp1 1
show bridge-domain 1 detail

#Examine l2 fib
show l2fib verbose
```
#### Lab6 NAT
```s

ip link add name vpp1outside type veth peer name vpp1outsidehost
ip link set dev vpp1outside up
ip link set dev vpp1ooutsidehost up
ip addr add 10.10.1.1/24 dev vpp1outsidehost
ip addr show vpp1outsidehost

```

### VPP Packet Tracing
```
trace add dpdk-input 10
trace add af-packet-input 10
show trace
```

### VPP Memory Usage
```
show memory verbose
show run
```
## Useful Debug CLI
### Interface command
[Here](https://fd.io/docs/vpp/v2001/reference/cmdreference/index.html)
#### Basic Interface command
```
show interface
show bridge-domain 
show hardware-interface
```
#### Create Interface command
```
vpp# create host-interface name vpp1
host-vpp1

vpp# set interface state host-vpp1 up


create loopvack interface

```
#### Set interface command
set interface IP address and bridge
```
set interface ip address vpp1 10.1.1.1/24
set interface ip address del vpp1 


set interface l2 bridge vpp1 2
//where 2 is the bridge-domain-id

set interface l2 bridge vpp1 2 bvi
set interface l3 vpp1


```
### Ip Command
#### ip route
```
ip route add 10.1.1.0/24 via 10.1.2.2
ip route del 10.1.1.0/24 via 10.1.2.2
```
#### ping
#### set ip address
#### show ip arp
```
show ip arp
```
#### show ip fib
```
show ip fib
```
### Snow Command
#### show l2fib
```
show l2fib
```





## Reference 参考链接
* [Build a Fast Network Stack with Vector Packet Processing (VPP) on an Intel® Architecture Server](https://software.intel.com/en-us/articles/build-a-fast-network-stack-with-vpp-on-an-intel-architecture-server)
* [Vector Packet Processor Documentation](https://buildmedia.readthedocs.org/media/pdf/my-vpp-docs/building-vpp/my-vpp-docs.pdf)
* [The Vector Packet Processor (VPP)](https://fd.io/docs/vpp/master/whatisvpp/index.html)
* [DPDK未来网络技术沙龙系列：FD.io及其关键组件VPP技术 视频](https://v.qq.com/x/page/x0694aqoeom.html)
* [vpp源码解读](https://blog.csdn.net/jqh9804?viewmode=contents)
* [于洋的博客](https://www.cnblogs.com/scottieyuyang/default.html?page=1)
* [VPP/DPDK使用](https://blog.csdn.net/shaoyunzhe/category_6538239.html)
* [VPP性能之一](https://blog.csdn.net/weixin_42265069/article/details/85780560#cache_5)
* [VPP环境搭建](http://www.isimble.com/2018/11/15/vpp-setup/)
* [赵占旭](https://zhaozhanxu.com/archives/page/8/)
* [编译安装VPP及运行(虚拟机环境)](https://blog.csdn.net/turbock/article/details/100578117)