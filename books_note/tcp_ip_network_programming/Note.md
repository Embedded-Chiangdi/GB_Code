# TCP/IP 网络编程
## A Quick Reference
### Server
```c
#include <sys/socket.h>
int socket(int domiain, int type, int protocol);
int bind(int sockfd, struct sockaddr *myaddr, soclen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
/*
Create a Server
Step one : creat socket fd
Step two : bind socket with allocating ip address and port
Step three : enter listen state to monitor net connections
Step four : accept connection and have some opreation on it
*/
```
### Client
```c
#include <sys/socket.h>
int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
/*
Create a Client
Step one : creat a socket fd
Step two : connect to server which you wanna to connected and do opreations
*/
```
## Socket Type and Protocol
As we have mentioned before, Create a scoket use a function called `socket(int domain, int type , int protocol);`, but we never explain any thing about it. Now we start get more details about this function.
```c
#include <sys/socket.h>
int socket(int domiain, int type, int protocol);
```

***
> * domain 套接字使用的协议族（Protocol family）
> * type 套接字数据传输类型信息
> * protocol 计算机间通信中使用的协议信息
***

### Protocol Family
* `PF_INET` IPv4(Used Most)
* `PF_INET6` IPv6
* `PF_LOCAL` 本地通信UNIX协议族
* `PF_PACKET` 底层套接字的协议族
* `PF_IPX` IPX Novell协议族
### Type
套接字类型指的是套接字的数据传输方式。
#### SOCK_STREAM 面向连接的套接字

#### SOCK_DGRAM 面向消息的套接字

## Allocat IP Address and Port
```c
struct sockaddr_in{
    sa_family_t sin_family; //Protocol Family
    uint16_t    sin_port; //Port
    struct in_addr  sin_addr;//IP_address
    char    sin_zero[8]; //No use
};
struct in_addr{
    In_addr_t s_addr;
}
```
***
>sin_family
* AF_INET   IPv4网络协议中使用的地址族
* AF_INET6  IPv6网络协议中使用的地址族
* AF_LOCAL  本地通信采用的UNIX协议的地址族
***
```c
struct sockaddr_in serv_addr;
if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
```
And what is `struct sockaddr` ?
```c
struct sockaddr{
    sa_family_t sin_family;
    char sa_data[14];
}
```

## Netwrok Address Init
```c
struct sockaddr_in addr;
char* serv_ip="110.123.34.221";
char* serv_port="7842";
memset(&addr,0,sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=inet_addr(serv_ip);
addr.sin_port=htons(atoi(serv_port));
```
Server netwrok address init
```c
struct sockaddr_in addr;
char * serv_port="9190";
memset(&addr,0,sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=htonl(INADR_ANY);
addr.sin_port=htons(atoi(serv_port));
```


# Reference
[Lec 26: Socket Addressing and Client Socket Programming](https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/26/lec.html#orgheadline1)