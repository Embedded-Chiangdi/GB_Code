#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define DFL_PROMPT ">"

void setup();

int main(){
    char *cmdline,*prompt,**arglist;
    int result;

    prompt=DFL_PROMPT;
    setup();

    while((cmdline = next_cmd(prompt,stdin)) != NULL)
    {
        if((arglist=splitline(cmdline))!=NULL){
            result = execute(arglist);
            freelist(arglist);

        }
        free(cmdline);
    }

    return 0;
    
}


void setup(){
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
}

void fatal(char *s1,char *s1,int n){
    fprintf(stderr,"Error : %s,%s\n",s1,s2);
    exit(n);
    
}