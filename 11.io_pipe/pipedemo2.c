#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CHILE_MESS "Child process is running \n"
#define PAR_MESS "Parent process is runing \n"
#define oops(m,x) {perror(m);exit(x);}


int main()
{
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;
    if(pipe(pipefd) == -1)
        oops("cannot get a pipe",1);
    switch(fork())
    {
        case -1:
            oops("cannot get a pipe",1);
        case 0:
            len=strlen(CHILE_MESS);
            while(1){
                if(write(pipefd[1],CHILE_MESS,len) != len)
                    oops("write",3);
                    sleep(5);
            }
        default:
            len=strlen(PAR_MESS);
            while(1)
            {
                if(write(pipefd[1],PAR_MESS,len)!=len)
                    oops("write",4);
                    sleep(1);
                    read_len=read(pipefd[0],buf,BUFSIZ);
                    if(read_len<=0)
                    break;
                    write(1,buf,read_len);
            }
    }

}

