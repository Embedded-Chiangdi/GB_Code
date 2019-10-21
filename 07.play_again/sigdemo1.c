#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void fun(int);
int main()
{
    int i;
    signal(SIGINT,fun);
    for(i=0;i<5;i++)
    {
        printf("hello\n");
        sleep(2);
    }
    return 0;
}
void fun(int signum)
{
    printf("OUCH!\n");
}