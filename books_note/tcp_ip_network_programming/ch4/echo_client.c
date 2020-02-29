#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char*argv[]){
    int serv_sock;
    struct sockaddr_in addr;
    char message[BUF_SIZE]={0};
    int str_len;

    if(argc!=3){
        printf("Usage: %s <ip> <port>",argv[0]);
        return 1;
    }

    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(argv[1]);
    addr.sin_port=htons(atoi(argv[2]));

    if(connect(serv_sock,(struct sockaddr *)&addr,sizeof(addr)) != 0)
        error_handling("connect failed");
    printf("connected");
    
   while(1)
   {
       fputs("Input message(Q to quiet):",stdout);
       fgets(message,BUF_SIZE,stdin);

       if(!strcmp(message,"q\n")|| !strcmp(message,"Q\n"))
            break;
        write(serv_sock,message,strlen(message));
        str_len=read(serv_sock,message,BUF_SIZE-1);
        message[str_len]=0;
        printf("Message from server: %s",message);

   }
    close(serv_sock);
    return 0;


    
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}