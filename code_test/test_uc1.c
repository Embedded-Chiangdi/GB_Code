#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv){
	char databuf[1];
	char datastat;
	snprintf(databuf,1,"%d",1);

        datastat = databuf[0];
        printf("databuf is : %s \r\ndatastat  is %d\r\n",databuf,datastat);
        return 0;

}
