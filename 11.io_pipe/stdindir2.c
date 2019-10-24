#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int fd;
    int newfd;
    char line[100];

    fgets(line,100,stdin);printf("%s",line);
    fd=open("/home/jiangdi/GB_Code/11.io_pipe/date",O_RDONLY);
    if(fd != 0)
    {
        fprintf(stderr,"Could not open date file\n");
        return 1;
    }
    newfd =dup2(fd,0);
    if(newfd != 0){
        fprintf(stderr,"Could not duplicate fd to 0 \n");
        exit(1);
    }
    close(fd);

    fgets(line,100,stdin);printf("%s",line);
}