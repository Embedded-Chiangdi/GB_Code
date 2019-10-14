#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/vfs.h>
#include <error.h>
#define Gsize (1024.00*1024.00*1024.00)
#define Msize (1024.00*1024.00)


double time_so_far();
float get_cpu_rate();
float get_memory_rate();
float get_disk_rate();

typedef struct occupy
{
    /* data */
    int user;
    int nice;
    int system;
    char name[10];

}CPU_OCCUPY;

typedef struct meminfo {
    char mem_str[16];
    char mem_size[16];
    int mem_total;
    int mem_free;
}MEM_INFO;

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
    int t;
    CPU_OCCUPY *ocpu,*ncpu;
    ocpu=(CPU_OCCUPY *)malloc(sizeof(CPU_OCCUPY));
    ncpu=(CPU_OCCUPY *)malloc(sizeof(CPU_OCCUPY));
    
    if((ocpu == NULL) || (ncpu == NULL))
        {
            perror("memory allocate failed\n");
            exit(1);
        }

    ti=time_so_far();
    f1=fopen("/proc/stat","r");
    fscanf(f1,"%s\t%d\t%d\t%d\n",ocpu->name,&ocpu->user,&ocpu->nice,&ocpu->system);
    fclose(f1);
    printf("%s\t%d\t%d\t%d\n",ocpu->name,ocpu->user,ocpu->nice,ocpu->system);
    sleep(1);

    tf=time_so_far();
    f1=fopen("/proc/stat","r");
    fscanf(f1,"%s\t%d\t%d\t%d\n",ncpu->name,&ncpu->user,&ncpu->nice,&ncpu->system);
    fclose(f1);
    printf("%s\t%d\t%d\t%d\n",ncpu->name,ncpu->user,ncpu->nice,ncpu->system);
    
    t=(ncpu->user+ncpu->nice+ncpu->system)-(ocpu->user+ocpu->nice+ocpu->system);
    printf("%d\n",t);
    printf("cpu usage: %.2f%%\n",( t/((tf-ti)*100) )*100 );
    free(ncpu);
    free(ocpu);
}

float get_memory_rate(){
    FILE *f1;
    MEM_INFO *mem_info;
    mem_info=(MEM_INFO *)malloc(sizeof(MEM_INFO));
    if(mem_info == NULL)
        {
            perror("memory allocate failed\n");
            exit(1);
        }
    f1=fopen("/proc/meminfo","r");
    fscanf(f1,"%s\t%d\t%s",mem_info->mem_str,&mem_info->mem_total,mem_info->mem_size);
    //printf("memory total is %d Kb\n",mem_info->mem_total);
    printf("memory total is %.2f Mb\n",mem_info->mem_total/1024.0);
    
    fscanf(f1,"%s\t%d\t%s",mem_info->mem_str,&mem_info->mem_free,mem_info->mem_size);
    //printf("memory free is %d Kb\n",mem_info->mem_free);
    printf("memory free is %.2f Mb\n",mem_info->mem_free/1024.0);
    fclose(f1);
    printf("men usage : %.2f%%\n",((mem_info->mem_total - mem_info->mem_free)*100.0)/mem_info->mem_total);
    free(mem_info);
    
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
 
        printf("Disk size of / is %.2f G\n",blocks*fs->f_bsize/Gsize);
        printf("Free Disk size of / is %.2f G\n",bfree*fs->f_bsize/Gsize);
        printf("Disk usage of / is %.2f%% \n",(blocks-bfree*)100.0/blocks);
}