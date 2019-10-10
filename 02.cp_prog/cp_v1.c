#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define LEN 4096
#define COPYMODE 0644
int main(int argc, char*argv[])
{
	int s_fd,d_fd;
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

    while((read(s_fd,buf,LEN)) > 0)
        write(d_fd,buf,LEN);

        close(s_fd);
        close(d_fd);
        return 0;

}
