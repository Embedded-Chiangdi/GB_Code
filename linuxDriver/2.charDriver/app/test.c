#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

static char userdata[]= "user data !";

int main(int argc, char *argv){
    int fd;
    int ret;
    char filename[20] = "/dev/charDev";
    char readbuf[50]= {0};
    char writebuf[50]= {0};

    
    if((fd = open(filename,O_RDWR)) < 0){
        printf("Cannot open file %s",filename);
        return -1;
    }


        if((ret = read(fd,readbuf,50)) < 0){
            printf("read file %s failed!\r\n",filename);
        }
        else{
            printf("read data :%s\r\n",readbuf);
            }
   
    
       
        memcpy(writebuf,userdata,sizeof(userdata));
        if((ret = write(fd,readbuf,50)) < 0)
            printf("write file %s failed!\r\n",filename);
     
 
    
    close(fd);
    printf("close\r\n");
    return 0;
}