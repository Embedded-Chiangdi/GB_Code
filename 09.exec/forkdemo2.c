#include <stdio.h>
int main(){
    printf("Before fork my pid id %d\n",getpid());
    fork();
    fork();
    fork();
    printf("After my pid is %d\n",getpid());

}