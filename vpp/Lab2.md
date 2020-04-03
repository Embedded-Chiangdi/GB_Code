# Lab2 实验
```
set int state vppeth3 up
set int state vppeth4 up
set int ip add vppeth3 10.60.22.122/16

loopback create
set int state loop0 up
set int l2 bridge loop0 1 bvi 
set int ip address loop0 192.168.1.1/24
set int state loop0 up



set int l2 bridge vppeth4 1
nat44 add interface address vppeth3
set interface nat44 in loop0 out vppeth3
ip route 0.0.0.0/0 via 10.60.0.1 via vppeth3
```