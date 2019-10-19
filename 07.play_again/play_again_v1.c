#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

#define Question "Do you want another transaction"
int get_response(char *);
void set_crmode();
void tty_mode(int how);
int main()
{
    int response;
    tty_mode(0);
    set_crmode();
    response=get_response(Question);
    tty_mode(1);

    // printf("response is %d \n",response);

    return response;
}
int get_response(char * question)
{
    int input;
    int tag=0;
    
    while (1)
    {
        printf("%s (y/n) ?\n", question );
        /* code */
        switch(input = getchar()){
            case 'q':   return 0;break;
            case 'y':
            case 'Y':   tag =0; break;
            case 'n':
            case 'N':
            case EOF: tag=1;break;
            default:
                tag = -1;
                printf("\ncannot understad %c, ",input);
                printf("please type y or n\n");
                break;
            }
         printf("\nresponse is %d \n",tag);
    }
    
}
void set_crmode()
{
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &=~ICANON;
    ttystate.c_cc[VMIN]=1;
    tcsetattr(0,TCSANOW,&ttystate);
    
}
void tty_mode(int how){
    static struct termios original_mode;
    if(how ==0)
        tcgetattr(0,&original_mode);
    else

        tcsetattr(0,TCSANOW,&original_mode);
    
    
}