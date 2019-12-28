#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char *argv[]){
    char *string="abcdefg";
    char *test,*buf;
    int i;
    buf=(char *)malloc(strlen(string)+1);
    memcpy(buf,string,strlen(string)+1);
    for(i=0;i<8;i++){
            test=buf;
            buf++;
           printf("After %d times atoi is %d\n",i+1,atoi(test)); 
    }
    return 0;
}
