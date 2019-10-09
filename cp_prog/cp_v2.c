#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define LEN 4096
#define COPYMODE 0644
int main(int argc, char*argv[])
{
	int s_fd,d_fd,flag_cp;
    char buf[LEN];
    if (argc != 3)
    {
        printf("usage: cp [sou] [dest]\n");
        return 1 ;
    }


    if((s_fd=open(*++argv,O_RDONLY)) == -1){
        printf("sour file error\n");
        return 1;
    }
        if((d_fd=creat(*++argv,COPYMODE)) == -1){
        printf("dest file error\n");
        return 1;
    }

    while((flag_cp = read(s_fd,buf,LEN)) > 0)
        if(write(d_fd,buf,flag_cp) != flag_cp)
            {
                printf("write error\n");
                return 1;
            }
        if(flag_cp == -1)
        {
            printf("read error \n");
            return 1;
        }

        if(close(s_fd) == -1 || close(d_fd) == -1)
            {
                printf("close error\n");
                return 1;
            }
        return 0;

}
