#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/vfs.h>
#include <error.h>
#include <string.h>
#include <memory.h>

#define Gsize (1024.00*1024.00*1024.00)
#define Msize (1024.00*1024.00)
#define CONFIG_LOCATION_BASE_DIR "/config/"
#define CONFIG_GATE_MEM     CONFIG_LOCATION_BASE_DIR"config_mem.txt"
#define CONFIG_GATE_DISK    CONFIG_LOCATION_BASE_DIR"config_disk.txt"
#define CONFIG_DISK_ERROR	CONFIG_LOCATION_BASE_DIR"config_disk_error.txt"

#define ALARM_FILE_BASE_DIR    "/config/alarm_dir/"
#define ALARM_DISK_FILE             ALARM_FILE_BASE_DIR"disk_alarm"
#define ALARM_MEM_FILE              ALARM_FILE_BASE_DIR"mem_alarm"
#define ALARM_DISK_ERROR_FILE       ALARM_FILE_BASE_DIR"disk_error_alarm"


#define SWITCH_ENABLE 1


#define MEM_ALARM 2
#define DISK_ALARM 3
#define DISK_ERROR_ALARM 4

//double time_so_far();
//float get_cpu_rate();
float get_memory_rate();
float get_disk_rate();
int read_config_gate(char *file_path,int *gate_switch,float *gate_value);
//int read_config_gate(float *gate_cpu,float *gate_mem,float *gate_disk);
//int check_stat(int item,float gate_value,float check_value);
char check_disk_error();
char compare_gate_value(float gate_value,float check_value);
int check_stat(int item,char *state,char *enable,float check_value);
int alarm_info_create(int item,float check_value);
typedef struct check_info{
    //float value_cpu;
    float value_mem;
    float value_disk;
} info_arrary;

typedef struct check_switch{
	int disk_error_switch;
    int mem_switch;
    int disk_switch;
}switch_array;
/****************************
if warn_disk_stat == 0
    system is safe and don't need to send mail.
if warn_disk_stat == 1
    system have already send a warn/alarm mail to wlan-support
if enable_warn_disk == 0
    system is safe
if enable_warn_disk == 1
    system need to send a alarm mail to wlan-support
the two idetify is set to avoid send mail only for one times 
when system is un-safe condition.
****************************/
typedef struct warn_stat{
    char warn_disk_stat;
    char warn_disk_error_stat;
    char warn_mem_stat;
    char enable_warn_disk;
    char enable_warn_disk_error;
    char enable_warn_mem;
}warn_stat_arrary;

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
    info_arrary g_info;
    info_arrary v_info;
	switch_array saSwitch;
    warn_stat_arrary saState;
    //float mem_ocu,disk_ocu;


    memset(&saState,0,sizeof(warn_stat_arrary));
	//read switch and gate value
    read_config_gate(CONFIG_GATE_MEM,&saSwitch.mem_switch,&g_info.value_mem);
    read_config_gate(CONFIG_GATE_DISK,&saSwitch.disk_switch,&g_info.value_disk);
	//read switch only
	read_config_switch(CONFIG_DISK_ERROR,&saSwitch.disk_error_switch);



	printf("MEM_SWITCH:%d\nDISK_SWITCH:%d\nDISK_ERROR_SWITCH:%d\n", saSwitch.mem_switch,
                                                                    saSwitch.disk_switch,
                                                                    saSwitch.disk_error_switch);
    printf("GATE_MEM:%.2f%%\nGATE_DISK:%.2f%%\n",g_info.value_mem,g_info.value_disk);
    printf("disk/disk_error/mem is %d-%d-%d\nenable_disk/disk_error/mem is %d-%d-%d\n"
                                                    ,saState.warn_disk_stat,
                                                    saState.warn_disk_error_stat,
                                                    saState.warn_mem_stat,
                                                    saState.enable_warn_disk,
                                                    saState.enable_warn_disk_error,
                                                    saState.enable_warn_mem);	
    while(1)
    {
        if(tTick_seconds%60 == 0)
        {
            v_info.value_mem=get_memory_rate();
            v_info.value_disk=get_disk_rate();
            saState.enable_warn_disk=compare_gate_value(g_info.value_disk,v_info.value_disk);
            saState.enable_warn_mem=compare_gate_value(g_info.value_mem,v_info.value_mem);
            saState.enable_warn_disk_error=check_disk_error();
            
            printf("New compare here is:mem value is %f disk value is %f\n",v_info.value_mem,v_info.value_disk);
            printf("After Compare disk is : enable=%d-stat=%d\n",saState.enable_warn_disk,
                                                                saState.warn_disk_stat);
            printf("After Compare mem  is : enable=%d-stat=%d\n",saState.enable_warn_mem,
                                                                saState.warn_mem_stat);
            if(saSwitch.disk_switch == SWITCH_ENABLE)
                check_stat(DISK_ALARM,&saState.warn_disk_stat,&saState.enable_warn_disk,v_info.value_disk);
            if(saSwitch.mem_switch == SWITCH_ENABLE)
                check_stat(MEM_ALARM,&saState.warn_mem_stat,&saState.enable_warn_mem,v_info.value_mem);
            if(saSwitch.disk_error_switch ==SWITCH_ENABLE)
                check_stat(DISK_ERROR_ALARM,&saState.warn_disk_error_stat,&saState.enable_warn_disk_error,0);
        }
        sleep(1);
        tTick_seconds++;
    }


    return 0;
}
int alarm_info_create(int item,float check_value){

    FILE *fp;
    char file_name[256];
    char command[256];
    switch (item)
    {
    case MEM_ALARM/* constant-expression */:
        strcpy(file_name,ALARM_MEM_FILE);
        sprintf(command,"free -h >> %s",file_name);
        printf("command is %s\n",command);
        /* code */
        break;
    case DISK_ALARM/* constant-expression */:
        strcpy(file_name,ALARM_DISK_FILE);
        sprintf(command,"df -h >> %s",file_name);
        printf("command is %s\n",command);
        /* code */
        break;
    case DISK_ERROR_ALARM/* constant-expression */:
        strcpy(file_name,ALARM_DISK_ERROR_FILE);
        sprintf(command,"echo \"Disk Error: Cann't write\" >> %s",file_name);
        printf("command is %s\n",command);
        /* code */
        break;
    default:
        break;
    }
    puts(file_name);
    if((fp=fopen(file_name,"w")) == NULL)
            {
                perror("file creat failed");
                return 1;
            }
        else
        fprintf(fp,"the Occupancy rate is %f\n",check_value);
        fclose(fp);
        system(command);
		return 0;

}


int check_stat(int item,char *state,char *enable,float check_value){

    if(*state == *enable)
    {
        //printf("value equal state:%d enable:%d \n",*state,*enable);
        return 0;
    }
    //printf("value is not eaual state:%d enable:%d\n",*state,*enable);
    if(*state == 1)
    {
        //memset(state,0,sizeof(char));
		*state=0;
        //printf("after alarm compare  state:%d enable:%d\n",*state,*enable);
    }
    else
    {
        alarm_info_create(item,check_value);
        *state=1;
        //memset(state,1,sizeof(char));
        //printf("after alarm compare  state:%d enable:%d\n",*state,*enable);
    }
    
    return 0;
}
char compare_gate_value(float gate_value,float check_value){
    if(gate_value < check_value)
        return 1;
    else
        return 0;
}

char check_disk_error(){
        if(0!=system("echo test > /config/write_enable.txt"))
            return 1;
        else 
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