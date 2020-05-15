#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    unsigned int i=0x17fe6;
    unsigned int l;
    int j;
    int k=500;
    j=i;
    l=k;
    printf("%08x unsigned int is %d\t int is %d\n",i,i,j);
    printf("%08d unsigned int is %d\t int is %d\n",k,l,l);
    
}