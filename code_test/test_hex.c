#include <stdio.h>
#include <stdlib.h>
int main(int argc, char*argv[]){
    unsigned int i=0x00000001;
    unsigned int j=0x00000010;
    unsigned int k=0x00000100;
    unsigned int m=32;
    printf("%04o %04x %d\n",i,i,i);
    printf("%04o %04x %d\n",j,j,j);
    printf("%04o %04x %d\n",k,k,k);
    printf("%08x\n",m<<6);
}