#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
pthread_t id1,id2;
void do_some_thing1()
{
    int i;
    for(i=0;i<100;i++){
        printf("do_some_thing1 %d\n",i);
    if(i==50)
    {
        printf("do_some_thing1 is going to exit\n");
        exit(1);
    }
    }
}
void do_some_thing2()
{
    int i;
    for(i=0;i<100;i++)
        printf("do_some_thing2 %d\n",i);

}
int main_loop()
{
    printf("enter main loop\n");
    printf("prepare to exit\n");
    //exit(1);
    printf("enter do_some_thing1\n");
    pthread_create(&id1,NULL,(void*)do_some_thing1,NULL);
    pthread_detach(id1);

    printf("enter do_some_thing2\n");
    pthread_create(&id2,NULL,(void*)do_some_thing2,NULL);
    pthread_detach(id2);
    while(1){
       sleep(500);
    };
    return 0;
}
int main(int argc , char *argv[])
{
    pid_t result;
    result=fork();
    if(result == -1)
    {
        printf("fork failed \n");
        exit(1);
    }

    switch(result)
    {
        case 0:
            printf("Child: enter dameon mode\n");
            main_loop();
            break;
        default:
            printf("Parent:exit at main();\n");
            exit(0);
        break;
    }

    return 0;
}