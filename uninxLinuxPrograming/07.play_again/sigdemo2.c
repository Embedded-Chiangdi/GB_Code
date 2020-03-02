#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    signal(SIGINT,SIG_IGN);
    printf("you can't stop me !\n");
    while (1)
    {
        /* code */
        sleep(1);
        printf("haha\n");
    }
    
}
