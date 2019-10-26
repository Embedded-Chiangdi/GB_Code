#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void main(){
    FILE *fp;
    fp =popen("mail admin backup","w");
    fprintf(fp,"Error with backup!!\n");
    pclose(fp);
}