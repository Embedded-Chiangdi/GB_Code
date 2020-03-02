#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{
    struct termios info;
    int rv;

    if((rv = tcgetattr(0,&info)) == -1)
    {
      perror("tcgetattr");
      exit(1);  
    }
    if(info.c_lflag& ECHO )
        printf("echo is on . since its bit is 1 \n");
    else
        printf("echo is off , since its bit is 0 \n");
    
    
}