#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if 1
int main(int argc,char**argv){
	int i=0;
	char *hex="1ab4";
	char *phex;
	unsigned int u=0;
	unsigned int *pu;
	char ch;
	phex=hex;
	pu=&u;
	
	for(i=0;i<4;i++){
		ch=*phex++;
		*pu <<=4;
		printf("%0x\t",*pu);
		if(ch >= '0' && ch <= '9') *pu|=ch - '0';
		else if (ch >= 'A' && ch <= 'F' ) *pu |= ch-('A'-10);
		else if (ch >= 'a' && ch <= 'f') *pu |= ch -('a' -10);
		else return 1;
		printf("%0x\n",*pu);
	}
	printf("%0x\n",*pu);
	return 0;
	
}

#endif
#if 0
int main(int argc , char **argv){
	char *hex =1ac3";
	char *end = NULL;
	unsigned int u;
	unsigned int *pu;
	u=0;
	pu=&u;
	pu=(unsigned int)strtol(hex,end,32);
	printf("%0x\n",*pu);
	return 0;
}
#endif 