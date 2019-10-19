#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
int main(int argc, char *argv[]){
    struct termios info;
    if(argc == 1 )
        exit(0);
    if(tcgetattr(0,&info) == -1)
        perror("tcgetattr");
    if(argv[1][0] == 'y')
        info.c_lflag |= ECHO;
    if(argv[1][0] == 'n')
        info.c_lflag &= ~ECHO;
    if(tcsetattr(0,TCSANOW,&info) == -1)
        perror("tcsetattr");
    
}