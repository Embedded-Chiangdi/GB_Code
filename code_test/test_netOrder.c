#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u8 unsigned char

int main(int argc, char *argv[]){
		u8* mask;
		
		mask= (u8 *)malloc(sizeof(u8)*32);
		if(mask==NULL){
			fprintf(stderr,"Allocate memory failed\n");
			return 1;
		}
		
		memset(mask,0,32*sizeof(u8));
		//mask[7]=~0;
		mask[7] = 0xff;
		//mask[7] |= 0x81;
		
		printf("%04x\n",mask[6]);
		printf("%04x\n",mask[8]);
		printf("%04x\n",mask[7]);
		return 0;
}