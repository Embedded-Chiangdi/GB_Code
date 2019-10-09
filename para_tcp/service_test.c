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

void str_echo(int socket_fd)
{
        char buf[MAXSIZE];
        int n;
        while( (n=read(socket_fd,buf,MAXSIZE)) > 0)
                write(socket_fd,buf,n);
        if(n < 0)
                printf("str_echo:read error\n");
}

int main(int argc, char **argv)
{
        int listen_fd,connect_fd,i;
        struct sockaddr_in service_addr;
        //char t_buf[MAXSIZE];
        //time_t ticks;
        int error_flag;
        pid_t pid_num;
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
        service_addr.sin_port = htons(9877);

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
                connect_fd = accept(listen_fd,(SA *)NULL,NULL);
                if(connect_fd < 0)
                {
                        printf("accept error\n");
                        return 1;
                }
                printf("connected %d times\n",++i);
                if ((pid_num =fork()) == 0)
                {
                        close(listen_fd);

                        str_echo(connect_fd);
                        //ticks=time(NULL);
                        //snprintf(t_buf,sizeof(t_buf),"\nback message time : %s",ctime(&ticks));
                        //write(connect_fd,t_buf,strlen(t_buf));

                        close(connect_fd);
                        exit(0);
                        printf("connected is off\n");
                }

                close(connect_fd);

        }
        return 0;
}
