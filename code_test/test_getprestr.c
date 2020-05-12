#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc , char *argv[]){
	char dst_ip[]="172.16.0.0/16";
	char *temp;
	char command[32]={0};
	printf("Size is %d\n",sizeof(dst_ip));
	if(NULL == (temp = strstr(dst_ip,"/")))
		printf("NOT FOUND\n");
	else{
	snprintf(command,temp-dst_ip+1,"%s",dst_ip);
	printf("%s\n",command);
} 
	return 0;
}
