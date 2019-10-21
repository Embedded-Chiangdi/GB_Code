#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define Question "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')


int get_response(char * questionm,int times );
void set_crmode();
void tty_mode(int how);
void set_noecho_mode();
void set_nodelay_mode();
char get_ok_char();

void fun(int)

int main()
{
    int response;
    tty_mode(0);
    //set_crmode();
    set_noecho_mode();
    set_nodelay_mode();
    signal(SIGINT,fun);
    signal(SIGQUIT,SIG_IGN);
    response=get_response(Question,TRIES);
    tty_mode(1);

    printf("response is %d \n",response);

    return response;
}
int get_response(char * question,int times )
{
    int input;
    while (1)
    {
        sleep(SLEEPTIME);
        printf("%s (y/n) ?\n", question );
        fflush(stdout);
        input=tolower(get_ok_char());
        if(input ='y')
            return 0;
        if(input ='n')
            return 1;
        if(times-- == 0)
            return 2;
        BEEP;
        /* code */
        // switch(input = getchar()){
        //     case 'q':   return 0;break;
        //     case 'y':
        //     case 'Y':tag =0; break;
        //     case 'n':
        //     case 'N':
        //     case EOF:tag=1;break;
        //     default:
        //         tag = -1;
        //         printf("cannot understad %c, ",input);
        //         printf("please type y or n\n");
        //         break;
        //     }
        // printf("response is %d \n",tag);
    }
    
}

char get_ok_char()
{
    int c;
    while ((c=getchar())!= EOF && strchr("yYnN",c) == NULL)
    {
        /* code */
    }
    return c;
    
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
    static int original_flag;
    if(how ==0)
    {
        tcgetattr(0,&original_mode);
        original_flag= fcntl(0,F_GETFL);
    }
    else
    {
        tcsetattr(0,TCSANOW,&original_mode);
        fcntl(0,F_SETFL,original_flag);
    } 
    
}
void set_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &=~ECHO;
    ttystate.c_cc[VMIN] =1;
    tcsetattr(0,TCSANOW,&ttystate);

    
}

void set_nodelay_mode(){
    int termflags;
    termflags = fcntl(0,F_GETFL);
    termflags |=O_NDELAY;
    fcntl(0,F_SETFL,termflags);
}
void fun (int sum)
{
    tty_mode(1);
    exit(1);
}