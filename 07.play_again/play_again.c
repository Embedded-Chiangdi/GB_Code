#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

#define Question "Do you want another transaction"
int get_response(char *);
int main()
{
    int response;
    response=get_response(Question);
    printf("response is %d \n",response);

    return response;
}
int get_response(char * question)
{
    printf("%s (y/n) ?", question );
    while (1)
    {
        /* code */
        switch(getchar()){
            case 'y':
            case 'Y':   return 0;
            case 'n':
            case 'N':
            case EOF: return 1;
        }
    }
    
}