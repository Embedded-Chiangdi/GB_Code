#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/vfs.h>
#include <error.h>
#include <string.h>

#define Gsize (1024.00*1024.00*1024.00)
#define Msize (1024.00*1024.00)
#define CONFIG_GATE_PATH "gate_config.txt"


#define CPU_WARN 1
#define MEM_WARN 2
#define DISK_WARN 3

double time_so_far();
float get_cpu_rate();
float get_memory_rate();
float get_disk_rate();
int read_config_gate(float *gate_cpu,float *gate_mem,float *gate_disk);
int check_stat(int item,float gate_value,float check_value);
typedef struct check_info{
    float value_cpu;
    float value_mem;
    float value_disk;
} check_arrry;

int main(int argc,char *argv[])
{
    int tTick_seconds=0;
    check_arrry g_info;
    check_arrry v_info;

    read_config_gate(&g_info.value_cpu,&g_info.value_mem,&g_info.value_disk);

    printf("%.2f %.2f %.2f\n",g_info.value_cpu,g_info.value_mem,g_info.value_disk);
    while(1)
    {
        if(tTick_seconds%60 == 0)
        {
            printf("tTick_seconds = %d\n",tTick_seconds);
            v_info.value_cpu=get_cpu_rate();
            v_info.value_mem=get_memory_rate();
            v_info.value_disk=get_disk_rate();
            printf("%.2f %.2f %.2f\n",v_info.value_cpu,v_info.value_mem,v_info.value_disk);
            check_stat(CPU_WARN,g_info.value_cpu,v_info.value_cpu);
            check_stat(MEM_WARN,20.0,v_info.value_mem);
            check_stat(DISK_WARN,20.0,v_info.value_disk);
            //check_stat(MEM_WARN,g_info.value_mem,v_info.value_mem);
            //check_stat(DISK_WARN,g_info.value_disk,v_info.value_disk);
        }
        sleep(1);
        tTick_seconds++;
    }


    return 0;
}
int check_stat(int item,float gate_value,float check_value){
    
    FILE *fp;
    char file_name[16];
    switch (item)
    {
    case CPU_WARN/* constant-expression */:
        strcpy(file_name,"CPU_WARN.tag");
        /* code */
        break;
    case MEM_WARN/* constant-expression */:
        strcpy(file_name,"MEM_WARN.tag");
        /* code */
        break;
    case DISK_WARN/* constant-expression */:
        strcpy(file_name,"DISK_WARN.tag");
        /* code */
        break;
    default:
        break;
    }
   puts(file_name);
    if(check_value > gate_value)
    {
        if((fp=fopen(file_name,"w")) == NULL)
            {
                perror("file creat failed");
                return 1;
            }
        else
                fclose(fp);
    }
    return 0;
}

int read_config_gate(float *gate_cpu,float *gate_mem,float *gate_disk){
    FILE *f1;
    if((f1=fopen(CONFIG_GATE_PATH,"r")) == NULL)
    {
        perror("open config file failed\n");
        exit(1);
    }
    fscanf(f1,"%f %f %f",gate_cpu,gate_mem,gate_disk);

    fclose(f1);
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
    char c_name[4];
    int user1,user2,nice1,nice2,system1,system2;

    ti=time_so_far();
    if((f1=fopen("/proc/stat","r")) == NULL){
        perror("open file failed \n");
        exit(1);
    }
    fscanf(f1,"%s\t%d\t%d\t%d\n",c_name,&user1,&nice1,&system1);
    fclose(f1);
    sleep(1);

    tf=time_so_far();
    if((f1=fopen("/proc/stat","r")) == NULL){
        perror("open file failed \n");
        exit(1);
    }
    fscanf(f1,"%s\t%d\t%d\t%d\n",c_name,&user2,&nice2,&system2);
    fclose(f1);
    t=(user1+nice1+system1)-(user2+nice2+system2);
    return (t/((tf-ti)*100))*100;
}

float get_memory_rate(){
    FILE *f1;
    char c_name[10];
    char d_name[10];
    int mem_total,mem_free;
    f1=fopen("/proc/meminfo","r");
    if(f1 == NULL)
    {
        perror("file open failed\n");
        exit(1);
    }
    fscanf(f1,"%s\t%d\t%s",c_name,&mem_total,d_name); 
    fscanf(f1,"%s\t%d\t%s",c_name,&mem_free,d_name);
    fclose(f1);
    return ((mem_total - mem_free)*100.0)/mem_total;
    
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
    return (blocks-bfree)*100.0/blocks;
}