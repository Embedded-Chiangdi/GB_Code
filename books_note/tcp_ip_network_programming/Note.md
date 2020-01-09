# TCP/IP 网络编程
# Part I 
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

# Part II
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
* 按序传输数据
* 传输的数据不存在边界
* 传输过程中数据不会消失
#### SOCK_DGRAM 面向消息的套接字
* 快速传输
* 非可靠传输
* 传输存在数据边界
* 每次传输的数据大小有限制
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
## Endian Conversions(字节序转换) and Network Endian(网络字节序)
In gernal, There are big endian and little endian in computer world for bytes transmission. Most of inters micro-crontroller are based on little endian. but netwrok transsission is big endian. So we should do endian conversions before  fill stuff in `sockaddr_in`.  
There are some functions help us to do so:
```c
//h stand for “host” in htons
//n stamd for “netwrok” in htons
//s stand for “short” in htons
//so htons stand for "host to network in short format" 
unsigned short htons(unsigned short);
unsigned short ntohs(unsigned short);、
//h stand for “host” in htons
//n stamd for “netwrok” in htons
//l stand for “long” in htons
//so htonl stand for "host to network in long format" 
unsigned long htonl(unsigned long);
unsigned long ntohl(unsigned long);
```
A example for endian conversions
```c
#include <stdio.h>
#include <arpa/inet.h>
int main(int argc, char *argv[]){
    unsigned short host_port=0x1234;
    unsigned short net_port;
    unsigned long host_addr=0x12345678;
    unsigned long net_addr;
    net_port=htons(host_port);
    net_addr=htonl(host_addr);
    printf("Host ordered port: %#x \n",host_port);
    printf("Network ordered port: %#x \n",net_port);
    printf("Host ordered address: %#x \n",host_addr);
    printf("Network ordered address: %#x \n",net_addr);
    return 0;
}
```
## IP Address Conversion
In gerenal, we always store IP address as a Dotted Decimal Notation format as a string. But in `sockaddr_in` is stored in 32 bit's int format.we could use follow function to do a conversion.
```c
#include <arpa/inet.h>
in_addr_t inet_addr(const char *string);
```
A example show it usages.
```c
#include <stdio.h>
#include <arpa/inet.h>
int main(int argc, char *argv[]){
    char *addr1="1.2.3.4";
    unsigned long conv_addr=inet_addr(addr1);
    printf("Network ordered integer addr : %#1x \n",conv_addr);
    return 0;
}
```
Bsides, Not only can function of `inet_addr` conver ip's string to 32 bits' int but also can check the correct of ip address.  
There is another function called `inet_aton` which work same effects as `inet_addr` . and we use it much more frequently.
```c
#include <arpa/inet.h>
int inet_aton(const char *string, struct in_addr *addr);
```
A example show it usages.
```c
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(int argc, char*argv[]){
    char *addr="192.168.1.1";
    struct sockaddr_in addr_inet;
    inet_aton(addr,&addr_inet.sin_addr);
    printf("Network ordered integer addr : %#x \n", addr_inet.sin_addr.s_addr);
}
```
## Netwrok Address Init
A example show how to Init a sockaddr.
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
## Achieve of Server
```c
#include <sys/socket.h>
int listen(int sock, int backlog);
``` 
> * sock 希望进入等待连接请求状态的套接字文件描述符
> * backlog 连接请求等待队列Queue的长度，若为数字5，则队列的长度最长为5，表示最多使用5个连接

```c
#include <sys/socket.h>
int accept(int sock, struct sockaddr *addr,socklen_t *addrlen);
```
> * sock 服务器套接字的文件描述符
> * addr 保存发起连接请求的客户端地址信息的变量地址值，调用函数后向传递来的地址参量填充客户端地址信息
> * addrlen 第二个参数addr结构体的长度，但是存有长度的变量地址。


Accept函数受理连接请求等待队列中等待处理的客户端连接请求。函数调用成功时，返回套接字描述符。
## UDP 
### Base on UDP I/O function
```c
#include <sys/socket.h>
ssize_t sendto(int sock, void *buff,size_t nbytes, int flags, struct sockaddr *to,socklen_t addrlen);
```
>sock 用于传输数据的UDP套接字文件描述符
>buff 保存待传输数据的缓冲地址值
>nbytes 待传输的数据长度，以字节为单位
>flags 可选项参数
>to     存有目标地址信息的sockaddr结构体变量的地址值
>addrlen 传递给参数to的地址值结构体变量长度

***
```c
#include <sys/socket.h>
ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);
```
>sock 用于传输数据的UDP套接字文件描述符
>buff 保存待传输数据的缓冲地址值
>nbytes 待传输的数据长度，以字节为单位
>flags 可选项参数
>from   存有发送端地址信息的sockaddr结构体变量的地址值
>addrlen 传递给参数from的地址值结构体变量长度

***
以上，是编写UDP程序最为核心的部分。
### Create connected Socket
```c
sock = socket(PF_INET, SOCK_DGRAM,0);
memset(&adr,0,sizeof(adr));
adr.sin_family=AF_INET;
addr.sin_addr.s_addr=./././.
addr.sin_port=....
connect(sock,(struct sockaddr *)&adr,sizeof(adr));//This is very important
```


# Part III
## Closed TCP/UDP connections
### Half closed connection
```c
#include <sys/socket.h>
int shutdown(int sock,int howto);
```
>sock 需要断开的套接字文件描述符
>howto 传递端口方式信息
>>SHUT_RD   断开输入流
>>SHUT_WR   断开输出流
>>SHUT_RDWR 同时端口I/O流


## Domain 
### Get ip by domain
```c
#include <netdb.h>
struct hostent *gethostbyname(const char *hostname);

struct hostent{
    char * h_name; //official name
    char **h_aliases;//alias list
    int h_addrtype;//host address type
    int h_length; //address length
    char **h_addr_list;//address list
}
```
>h_name 官方域名
>h_aliases  其他域名
>h_addrtype IP地址族信息
>h_length   IP地址长度
>h_addr_list

### Get domain by ip
```c
#include <netdb.h>
struct hostent *gethostbyaddr(const char *addr, socklen_t len, int family);
```
>addr   含有IP地址信息
>len    第一个参数传递的地址信息的字节数，若为IPv4时为4，IPv6时为16.
>family 传递地址族信息，IPv4时为AF_INET，IPv6为AF_INET6

## Socket Options
```c
#include <sys/socket.h>
int getsocketopt(int sock, int level, int optname,void * optval, socklen_t *optlen);
```
>sock       用于查看选项套接字文件描述符
>level      要查看的可选项的协议层
>optname    要查看的可选项名
>optval     保存查看结果的缓冲地址
>optlen     向第四个参数optval传递的缓冲大小。调用函数后，该变量中保存通过第四个参数返回的可选项信息的字节数

```c
#include <sys/socket.h>
int setsocketopt(int sock, int level, int optname, const void *optbal, socklen_t optlen);
```
>sock       用于查看选项套接字文件描述符
>level      要查看的可选项的协议层
>optname    要查看的可选项名
>optval     保存查看结果的缓冲地址
>optlen     向第四个参数optval传递的缓冲大小。调用函数后，该变量中保存通过第四个参数返回的可选项信息的字节数

```
optlen=sizeof(option);
option=TRUE;
setsockopt(serv_sock, SOL_SOCKET,SO_REUSEADDR,(void *)&option,optlen);
```
# Part III
## Muliti Process Server

# Reference
[Lec 26: Socket Addressing and Client Socket Programming](https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/26/lec.html#orgheadline1)