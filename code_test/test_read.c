#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_READ 10

int main(int argc,char*argv[]){
    char buffer[MAX_READ+1];
    int count;
    int fd;
    fd=open("test.txt",O_RDONLY);
    if(fd == -1)
        return 1;
    
    if((count=read(fd,buffer,MAX_READ)) == -1)
        return 1;
    buffer[count]='\0';
    printf("The input data was %s \n",buffer);
    return 0;
}