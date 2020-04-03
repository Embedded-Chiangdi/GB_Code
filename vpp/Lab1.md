# 拓扑结构
## 执行代码命令
```s
ip link add vpp1out type veth peer name eth3_v
ip link set dev vpp1out up
ip link set dev eth3_v up
ip addr add 192.168.2.2/24 dev eth3_v
ip addr show eth3_v


create host-interface name vpp1out
show hardware
set int state host-vpp1out up
show int
set int ip address host-vpp1out 192.168.2.1/24
show int addr
```