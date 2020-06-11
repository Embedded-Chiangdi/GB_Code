#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc , char *argv[]){
	char vppInterface[]= "bvi0";

	if(NULL != strstr(vppInterface,"."))
		printf("exist .\n");
	else
	{
		printf("not exist . \n");

	}
	return 0;
	
#if 0
	char dst_ip[]="172.16.0.0";
	char *temp;
	if(NULL == (temp = strstr(dst_ip,"/")))
		printf("NOT FOUND\n");
	else 
	printf("Found:%s\n",temp);
	return 0;
#endif
}
