#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(int argc, char*argv[]){
    char *addr="192.168.1.1";
    struct sockaddr_in addr_inet;
    inet_aton(addr,&addr_inet.sin_addr);
    printf("Network ordered integer addr : %#x \n", addr_inet.sin_addr.s_addr);
}