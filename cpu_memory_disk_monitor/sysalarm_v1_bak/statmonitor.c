#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/vfs.h>
#include <error.h>
#include <string.h>

#define Gsize (1024.00*1024.00*1024.00)
#define Msize (1024.00*1024.00)
#define CONFIG_GATE_PATH    "gate_config.txt"
#define CONFIG_GATE_MEM     "/config/config_mem.txt"
#define CONFIG_GATE_DISK    "/config/config_disk.txt"

#define CONFIG_DISK_ERROR	"/config/config_disk_error.txt"

#define SWITCH_ENABLE 1

#define CPU_WARN 1
#define MEM_WARN 2
#define DISK_WARN 3

//double time_so_far();
//float get_cpu_rate();
float get_memory_rate();
float get_disk_rate();
int read_config_gate(char *file_path,int *gate_switch,float *gate_value);
//int read_config_gate(float *gate_cpu,float *gate_mem,float *gate_disk);
//int check_stat(int item,float gate_value,float check_value);
int check_stat(int item,float gate_value,float check_value);
int check_disk_error();


typedef struct check_info{
    //float value_cpu;
    float value_mem;
    float value_disk;
    int mem_switch;
    int disk_switch;
} check_arrry;

typedef struct check_switch{
	int disk_error_switch;
}switch_array;

// typedef struct cpu_info
// {
//     /* data */
//     int user;
//     int nice;
//     int system;
//     int idle;
//     int iowait;
//     int irq;
//     int softirq;
//     int sum1;
//     int sum2;
// } cpu_array;


int main(int argc,char *argv[])
{
    unsigned int tTick_seconds=0;
    check_arrry g_info;
    check_arrry v_info;
	switch_array saSwitch;
    float mem_ocu,disk_ocu;
	//read switch and gate value
    read_config_gate(CONFIG_GATE_MEM,&g_info.mem_switch,&g_info.value_mem);
    read_config_gate(CONFIG_GATE_DISK,&g_info.disk_switch,&g_info.value_disk);
	//read switch only
	read_config_switch(CONFIG_DISK_ERROR,&saSwitch.disk_error_switch);

	printf("%d %d %d\n",g_info.mem_switch,g_info.disk_switch,saSwitch.disk_error_switch);
    printf("%.2f %.2f\n",g_info.value_mem,g_info.value_disk);
	
    while(1)
    {
        if(tTick_seconds%60 == 0)
        {
            printf("tTick_seconds = %d\n",tTick_seconds);
            //v_info.value_cpu=get_cpu_rate();
            mem_ocu=get_memory_rate();
            disk_ocu=get_disk_rate();
            printf("%.2f %.2f\n",mem_ocu,disk_ocu);
            //check_stat(CPU_WARN,g_info.value_cpu,v_info.value_cpu);
            if(g_info.mem_switch == SWITCH_ENABLE)
                check_stat(MEM_WARN,g_info.value_mem,mem_ocu);
            if(g_info.disk_switch == SWITCH_ENABLE)
                check_stat(DISK_WARN,g_info.value_disk,disk_ocu);
        }
		if(tTick_seconds%3600){
			if(saSwitch.disk_error_switch ==SWITCH_ENABLE)
				check_disk_error();
		}

        sleep(1);
        tTick_seconds++;
    }


    return 0;
}
int check_disk_error(){
        if(0!=system("echo test > /config/write_enable.txt"))
            system("touch /config/DISK_ERROR.tag");

	}
int check_stat(int item,float gate_value,float check_value){
    
    FILE *fp;
    char file_name[64];
    switch (item)
    {
    case CPU_WARN/* constant-expression */:
        strcpy(file_name,"/config/CPU_WARN.tag");
        /* code */
        break;
    case MEM_WARN/* constant-expression */:
        strcpy(file_name,"/config/MEM_WARN.tag");
        /* code */
        break;
    case DISK_WARN/* constant-expression */:
        strcpy(file_name,"/config/DISK_WARN.tag");
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

int read_config_gate(char *file_path,int *gate_switch,float *gate_value){
    FILE *f1;
    if((f1=fopen(file_path,"r")) == NULL)
    {
        perror("open config file failed\n");
        exit(1);
    }
    fscanf(f1,"%d %f",gate_switch,gate_value);
    fclose(f1);
    return 0;
}

int read_config_switch(char *file_path,int *gate_switch){
    FILE *f1;
    if((f1=fopen(file_path,"r")) == NULL)
    {
        perror("open config file failed\n");
        exit(1);
    }
    fscanf(f1,"%d",gate_switch);
    fclose(f1);
    return 0;
}
// double time_so_far(){
//     struct timeval tp;
//     if(gettimeofday(&tp,(struct timezone *)NULL) == -1)
//         perror("gettimeofday");
//     return ((double)(tp.tv_sec))+(((double)tp.tv_usec)*0.000001);
// }

// float get_cpu_rate(){
//     FILE *f1;
//     double ti,tf;
//     int t;
//     char c_name[4];
//     int user1,user2,nice1,nice2,system1,system2;

//     ti=time_so_far();
//     if((f1=fopen("/proc/stat","r")) == NULL){
//         perror("open file failed \n");
//         exit(1);
//     }
//     fscanf(f1,"%s\t%d\t%d\t%d\n",c_name,&user1,&nice1,&system1);
//     fclose(f1);
//     sleep(1);

//     tf=time_so_far();
//     if((f1=fopen("/proc/stat","r")) == NULL){
//         perror("open file failed \n");
//         exit(1);
//     }
//     fscanf(f1,"%s\t%d\t%d\t%d\n",c_name,&user2,&nice2,&system2);
//     fclose(f1);
//     t=(user1+nice1+system1)-(user2+nice2+system2);
//     return (t/((tf-ti)*100))*100;
// }
// float get_cpu_rate()
// {
//     FILE *f1;
//     cpu_array ocpu;
//     cpu_array ncpu;
//     char c_name[4];
//     int work_priod,total_priod;
//     if((f1=fopen("/proc/stat","r")) == NULL){
//         perror("open file failed \n");
//         exit(1);
//     }
//     fscanf(f1,"%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",c_name,&ocpu.user,&ocpu.nice,&ocpu.system,&ocpu.idle,&ocpu.iowait,&ocpu.irq,&ocpu.softirq);
//     sleep(1);
//     fscanf(f1,"%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",c_name,&ncpu.user,&ncpu.nice,&ncpu.system,&ncpu.idle,&ncpu.iowait,&ncpu.irq,&ncpu.softirq);
//     ocpu.sum1=ocpu.nice+ocpu.user+ocpu.system+ocpu.idle+ocpu.iowait+ocpu.irq+ocpu.softirq;
//     ocpu.sum2=ocpu.nice+ocpu.user+ocpu.system;

//     ncpu.sum1=ncpu.nice+ncpu.user+ncpu.system+ncpu.idle+ncpu.iowait+ncpu.irq+ncpu.softirq;
//     ncpu.sum2=ncpu.nice+ncpu.user+ncpu.system;
//     work_priod=ncpu.sum2-ocpu.sum2;
//     total_priod=ncpu.sum1-ocpu.sum1;
//     //printf("%d",work_priod/total_priod);
//     return work_priod/total_priod*100.0;


// }
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