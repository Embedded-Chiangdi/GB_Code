#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    int i;
    printf("Number of arg:%d,Arg are :\n",argc);
    for(i=0;i<argc;i++)
        printf("args[%d] : %s \n",i,argv[i]);
    fprintf(stderr,"This message is sent to stderr.\n");
    return 0;

}