#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <error.h>

#define MAXSIZE 100
#define SA struct sockaddr
#define LISTENQ 1024

int main(int argc, char **argv)
{
	int listen_fd,connect_fd,i,len;
	struct sockaddr_in service_addr,cli_addr;
	char t_buf[MAXSIZE];
	time_t ticks;	
	int error_flag;
	i=0;
	listen_fd = socket(AF_INET,SOCK_STREAM, 0);
	if(listen_fd < 0)
	{
		printf("socket error\n");
		return 1;
	}
	
	bzero(&service_addr,sizeof(service_addr));
	
	service_addr.sin_family = AF_INET;
	service_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	service_addr.sin_port = htons(IPPORT_DAYTIME);

	error_flag=bind(listen_fd,(SA *)&service_addr, sizeof(service_addr));
	if(error_flag < 0)
	{
	printf("bind error\n");
	return 1;
	}
		
	error_flag=listen(listen_fd,LISTENQ);
	if(error_flag < 0)
	{
	printf("listen error\n");
	return 1;
	}
	
	for ( ; ; )
	{
	len=sizeof(cli_addr);
	connect_fd = accept(listen_fd,(SA *)&cli_addr,&len);
	
	if(connect_fd < 0)
	{
		printf("accept error\n");
		return 1;
	}
	printf("connected %d times\n",++i);
	connect_fd = accept(listen_fd,(SA *)&cli_addr,&len);
	printf("connection from %s,port %d\n",
	inet_ntop(AF_INET,&cli_addr.sin_addr,
	t_buf,sizeof(t_buf)),ntohs(cli_addr.sin_port));

	
	ticks=time(NULL);
	snprintf(t_buf,sizeof(t_buf),"%s",ctime(&ticks));
	write(connect_fd,t_buf,strlen(t_buf));
	
	close(connect_fd);
	
	}

}
