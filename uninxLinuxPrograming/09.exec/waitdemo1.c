#include <stdio.h>
#define DELAY 2
void child_mode();
void parent_mode();

int main(){
    int newpid;
    printf("before : mypid is %d\n",getpid());
    if((newpid=fork()) == -1)
        perror("fork");
    else if(newpid == 0)
        child_mode(DELAY);
    else
        parent_mode(newpid);

}

void child_mode(int delay)
{
    printf("child %d here, will sleep for %d seconds \n",getpid(),delay);
    sleep(delay);

    printf("child done, about to exit\n");    
}


void parent_mode(int childpid){
    int wait_rv;
    wait_rv=wait(NULL);
    printf("waiting done \n");
}