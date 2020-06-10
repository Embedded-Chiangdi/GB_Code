#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main(int argc,char **argv){
    pid_t pid_local;
    FILE *fp;
    int i = 30;
    pid_local = getpid();

    if((fp = fopen("lock.txt","w")) == NULL){
        printf("file open error\n");
        return 1;
    }
    printf("wait.....\n");
    if(flock(fp->_fileno,LOCK_EX) != 0){//LOCK
        printf("file lock by others\n");
        return 2;
    }
    printf("pid %d lock\n",pid_local);
    while(i){
        i--;
        printf("PID %d wait %d s\n",pid_local,i);

        sleep(1);
    }
    fclose(fp);
    flock(fp->_fileno,LOCK_UN);//UNLOCK
    printf("pid %d unlock",pid_local);
    return 0;
}