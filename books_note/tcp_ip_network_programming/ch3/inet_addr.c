#include <stdio.h>
#include <arpa/inet.h>
int main(int argc, char *argv[]){
    char *addr1="1.2.3.4";
    unsigned long conv_addr=inet_addr(addr1);
    printf("Network ordered integer addr : %#1x \n",conv_addr);
    return 0;
}