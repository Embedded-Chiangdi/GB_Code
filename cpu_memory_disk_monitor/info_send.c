#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 64
#define HOSTIP_DEVICE "ens33"
#define MAIL_CONFIG_FILE "mail_user.txt"
#define CPU_WARN_TAG "CPU_WARN.tag"
#define MEM_WARN_TAG "MEM_WARN.tag"
#define DISK_WARN_TAG "DISK_WARN.tag"

int get_device_ip_address(char *buf);
int get_mail_address(char *buf);
int check_warn_file(char *buf,char *ip_buf,char * mail_buf);
int mail_delay_send(char *buf);
int main (int argc, const char * argv[]) {
   
    char ip_address[BUF_SIZE];
    char mail_address[BUF_SIZE];
    unsigned int icTick=0;
    get_device_ip_address(ip_address);
    get_mail_address(mail_address);
    printf("Email is %s",mail_address);
    printf(" ipaddress is %s ",ip_address);
    while (1)
    {
        if(icTick%60 == 0)
        {   
            printf("60icTick = %d \n",icTick);
            check_warn_file(CPU_WARN_TAG,ip_address,mail_address);
            check_warn_file(MEM_WARN_TAG,ip_address,mail_address);
            check_warn_file(DISK_WARN_TAG,ip_address,mail_address);
        }
        if(icTick%3600 == 0)
        {
            printf("3600icTick = %d \n",icTick);
            mail_delay_send(CPU_WARN_TAG);//remove the sended flag to enable check_warn_file function.
            mail_delay_send(MEM_WARN_TAG);
            mail_delay_send(DISK_WARN_TAG);
        }
        sleep(1);
        icTick++;
    }
    
    //puts(ip_address);
    return 0;
}
int mail_delay_send(char *buf)
{
    char sended_tag[64];
    char command[128];
    sprintf(sended_tag,"%s.sended",buf);
    if((access(sended_tag,F_OK)) == 0 )
    {
        sprintf(command,"rm -f %s",sended_tag);
        system(command);
    }
    return 0;
}

int get_mail_address(char *buf)
{
    FILE *fp;
    if((fp=fopen(MAIL_CONFIG_FILE,"r")) ==NULL )
    {
        perror("fail to read file\n");
        return 1;
        //exit(1);
    }
    fscanf(fp,"%s",buf);
    fclose(fp);
    return 0;
}
int check_warn_file(char *buf,char *ip_buf,char *mail_buf)
{
    char command[128];
    char sended_tag[64];
    sprintf(sended_tag,"%s.sended",buf);
    if((access(buf,F_OK) == 0) && (access(sended_tag,F_OK) != 0))
        {
            printf("warn: %s\n",buf);

            sprintf(command,"echo %s | mailx -v -s \"%s\" %s",buf,ip_buf,mail_buf);
            printf("command is %s\n",command);
            system(command);
            
            sprintf(command,"rm -f %s",buf);
            printf("command is %s\n",command);
            system(command);
            
            sprintf(command,"touch %s",sended_tag);//Set the sended flag to avoid high frequency transmission
            printf("command is %s\n",command);
            system(command);

        }
        

    return 0;
}
int get_device_ip_address(char *buf){
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            if(strcmp(HOSTIP_DEVICE,ifa->ifa_name) == 0)
                sprintf(buf,"%s",addressBuffer); 
        } 
        // else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
        //     // is a valid IP6 Address
        //     tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
        //     char addressBuffer[INET6_ADDRSTRLEN];
        //     inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
        //     printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        // } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return 0;
}