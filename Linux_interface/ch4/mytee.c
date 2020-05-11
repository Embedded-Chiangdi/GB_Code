#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFSIZE
#define BUFSIZE 1024
#endif

void errExit(char *buf);
int main(int argc , char** argv){

    int out,rcount,wcount;
    char buff[BUFSIZE]={0};
    if(argc == 1 || !strncmp("-h",argv[1],sizeof("-h")) || !strncmp("--help",argv[1],sizeof("--help"))){
        printf("%s file \n",argv[0]);
        return 0;
    }    
    if(!strncmp("-a",argv[1],sizeof("-a"))){
        out=open(argv[2],O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
        printf("append");
    }
    else
         out=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    while((rcount=read(0,buff,BUFSIZE)) > 0)
        if((wcount=write(out,buff,rcount))!=rcount){
            errExit("write");
            return 1;
        }
    if(rcount == -1){
        errExit("read");
        return 1;
    }
    close(out);
    return 0;
}
void errExit(char *buf){
    write(2,buf,sizeof(buf));
}