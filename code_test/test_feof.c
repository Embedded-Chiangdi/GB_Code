#include <stdio.h>
#include <stdlib.h>
#define TEST_FILE_PATH "test.txt"
int main(){
	FILE *fp;
	char c;
	printf("Openning the file to test feod function\n");
	fp=fopen(TEST_FILE_PATH,"r");
	if(fp == NULL)
	{
	printf("Could not open the file \n");
	exit(1);
	}
	printf("Start reading file \n");
	while(1)
	{	
	c=fgetc(fp);
	if(feof(fp))
		{	printf("The last word is %d\n",c);
			break;}
	printf("%c",c);

	}
	printf("Close the file as end of the file is reached\n");
	fclose(fp);
	return 0;
}
