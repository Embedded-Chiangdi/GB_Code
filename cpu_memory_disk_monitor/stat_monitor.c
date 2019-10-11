#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <sys/vfs.h>
#include <error.h>
#define Gsize (1024.00*1024.00*1024.00)
#define Msize (1024.00*1024.00)

#ifndef EXT2_SUPER_MAGIC
#define EXT2_SUPER_MAGIC 0xef53
#endif

double time_so_far();
float get_cpu_rate();
float get_memory_rate();
float get_disk_rate();

int main(int argc,char *argv[])
{
    get_cpu_rate();
    get_memory_rate();
    get_disk_rate();
    return 0;
}
double time_so_far(){
    struct timeval tp;
    if(gettimeofday(&tp,(struct timezone *)NULL) == -1)
        perror("gettimeofday");
    return ((double)(tp.tv_sec))+(((double)tp.tv_usec)*0.000001);
}
float get_cpu_rate(){
    FILE *f1;
    double ti,tf;
    char c[10],d[10];
    int t,i1,i2,i3,i4,i5,i6;
    
    ti=time_so_far();
    f1=fopen("/proc/stat","r");
    fscanf(f1,"%s\t%d\t%d\t%d\n",c,&i1,&i2,&i3);
    fclose(f1);
    printf("%s\t%d\t%d\t%d\n",c,i1,i2,i3);
    usleep(1000000);

    tf=time_so_far();
    f1=fopen("/proc/stat","r");
    fscanf(f1,"%s\t%d\t%d\t%d\n",c,&i4,&i5,&i6);
    fclose(f1);
     printf("%s\t%d\t%d\t%d\n",c,i4,i5,i6);
    t=(i4+i5+i6)-(i1+i2+i3);
    printf("%d\n",t);
    printf("cpu usage: %.2f%%\n",( t/((tf-ti)*100) )*100 );

}
float get_memory_rate(){
    FILE *f1;
    int itemp1,itemp2;
    char c[10],d[10];

    f1=fopen("/proc/meminfo","r");
    fscanf(f1,"%s\t%d\t%s",c,&itemp1,d);
    printf("memory total is %d Kb\n",itemp1);
    printf("memory total is %.2f Mb\n",itemp1/1024.0);
    fscanf(f1,"%s\t%d\t%s",c,&itemp2,d);
    printf("memory free is %d Kb\n",itemp2);
    printf("memory free is %.2f Mb\n",itemp2/1024.0);
    fclose(f1);
    printf("men usage : %.2f%%\n",((itemp1-itemp2)*100.0)/itemp1);

}

float get_disk_rate(){
    struct statfs *fs;
    long long blocks,bfree;
    if(statfs("/",fs) != 0)
        {
            perror("stafts");
            printf("exit\n");
            exit(1);
        }
    blocks=fs->f_blocks;
    bfree=fs->f_bfree;
    //if(fs.f_type == EXT2_SUPER_MAGIC)
    //{
        printf("Disk size of / is %.2f G\n",blocks*fs->f_bsize/Gsize);
        printf("Free Disk size of / is %.2f G\n",bfree*fs->f_bsize/Gsize);
        printf("Disk usage of / is %.2f%% \n",bfree*100.0/blocks);
    //}
}