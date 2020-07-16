#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static my_putchar(char mychar){
	
	int i = mychar - ' ';
	printf("%d\r\n",i);
}


static void show_string(char *istring){
	char *temp = istring;
	while(*temp != '\0'){
		putchar(*temp);
		my_putchar(*temp++);
		
	}
	
}

int main(int argc, char **argv[]){
	
	char test1[]= "This is a test";
	char *test2 = "This is a test";
	
	show_string(test2);
	
	
}