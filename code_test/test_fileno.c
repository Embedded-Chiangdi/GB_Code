#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    FILE *fp;
    int fd;
    fp = fopen("lock.txt", "r");
    if((fd = fileno(fp)) == -1){
        printf("stream to fd fail\n");
        return 1;
    }
    printf("fd = %d\n",fd);
    fclose(fp);
    return 0;
}