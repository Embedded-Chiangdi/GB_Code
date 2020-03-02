#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd;
    char line[100];
    close(0);
    fd=open("/etc/passwd",O_RDONLY);
    if(fd!=0)
    {
        fprintf(stderr,"could not open data as fd 0 \n");
        exit(1);      
    }

    fgets(line,100,stdin);
    printf("%s",line);
    
    //fgets(line,100,stdin);printf("%s",line);
    //fgets(line,100,stdin);printf("%s",line);
    return 0;
}
