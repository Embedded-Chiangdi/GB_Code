#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc,char**argv){
	char s1[]="Hello";
	char s2[]="\"hello\"";
	printf("String is : %s strlen is :%d\n",s1,strlen(s1));
	printf("String is : %s strlen is :%d\n",s2,strlen(s2));
}