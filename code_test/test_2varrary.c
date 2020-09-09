#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PAGE_NUMBER 3
#define COLUMN_NUMBER 4

int updatebuffer(unsigned char *buffer){
    while(*buffer){
        printf("%d\n",*buffer);
        buffer++;
    }
}

int main(int argc , char **argv){

    unsigned char DisplayBuffer[PAGE_NUMBER][COLUMN_NUMBER] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

    updatebuffer(DisplayBuffer[0]);


    return 0;

}