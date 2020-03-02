#include <stdio.h>
#include <signal.h>
void wakeup(int );
int main()
{   
    printf("about to sleep for 4 seconds\n");
    signal(SIGALRM,wakeup);
    alarm(4);
    pause();
    //printf("4 seconds wait \n");

    printf("Morning so soon ? \n");
    
    return 0;
}
void wakeup(int signum)
{
    printf("Alarm received from kernel\n");
}
