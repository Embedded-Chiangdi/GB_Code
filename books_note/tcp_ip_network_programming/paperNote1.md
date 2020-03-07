# TCP/IP网络编程 
## 什么是套接字？
Sockets allow communication between two different processes on the same or different machines. To be more precise, it's a way to talk to other computers/programs using standard Unix file descriptors. In early, Sockets were designed to implement the client-server model for interprocess communication.
### 套接字类型
#### Stream socket : 
After the connection has been established, data can be read from and written to these socets as a byte stream. The socket type is `SOCK_STREAM`.
* bidirectional （双向通信）
* reliable（可靠传输）
* sequenced(有序)
* unduplicated flow of data with no record boundaries（无数据边界）
#### Datagram sockset
* bidirectional（双向通信）
* unsequenced（乱序，非可靠）
* boundaries（数据边界，且存在传输数据大小限制）
## 如何创建套接字？
创建套接字通常是为了进行通信，我们以服务器-客户端为模型，简单阐述如何创建套接字？创建套接字都需要调用哪些函数？调用函数中有哪些需要注意的地方？
### 服务器端
1. 创建 套接字
2. 注册 服务器的IP及端口
3. 绑定 服务器IP和端口
4. 设置 监听端口
5. 等待 连接

以上就是创建服务器端套接字的5个步骤。
例程如下：
```c
//传入参数1 argv[1] 为端口号
#define BUF_SIZE 128

int serv_sock,clnt_sock;
struct sockaddr_in serv_add,clnt_addr;
chat buf[BUF_SIZE]={0};
socklen_t clnt_addr_size;

serv_sock=socket(PF_INET,SOCK_STREAM,0);

serv_addr.sin_familt=AF_INET;
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
serv_addr.sin_port=htns(argv[1]);

bind(serv_sock,(struct sockaddr*)&serv_sock,sizeof(serv_addr);
listen(serv_sock,10);
accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size)
```
第8行代码   创建套接字  
第10-12行代码   填充套接字IP和端口信息。
第14行代码 给套接字绑定IP地址   
注：A remote process has no way to refer to a socket until an address is bound to it. Communicating processes are connected through addresses. The bind(3SOCKET) call allows a process to specify the local address of the socket
第15行代码   设置监听并规定最大等待队列  
注：specifies the maximum number of outstanding connections that might be queued.
第16行代码     


### 客户端
1. 创建 套接字
2. 注册 待连接服务器的IP及端口
3. 连接 服务器

以上是创建客户端套接字的3个步骤

