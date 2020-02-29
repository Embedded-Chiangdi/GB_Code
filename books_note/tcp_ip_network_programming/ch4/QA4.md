* 1.简述TCP/IP 4层协议栈 说明TCP 和 UDP 经过的层级结构差异？
* A：
* 2.链路层的作用
* A:
* 3.IP层的作用
* A: 路径选择和转发
* 4.客户端调用connect函数向服务器发送连接请求。服务器调用哪个函数后，客户端可以调用connect函数
* A:
* 5.什么时候创建连接请求等待队列？有何作用？与accept有什么关系？
* A:
* 6.

TCP的服务器断默认函数调用顺序：
1. socket()
2. bind()
3. listen()
4. accept()
5. read() / write()
6. close()

