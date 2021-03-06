#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void do_ls(char []);
void show_stat_info(char *,struct stat *);
void mode_to_letters(int,char[]);
void dostat(char *);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc , char *argv[]){
    if(argc == 1 )
        do_ls(".");
    else
    {
        while(--argc)
        {
            printf("%s:\n",*++argv);
            do_ls(*argv);

        }

    }
    return 0;
}
void do_ls(char dirname[])
{
    DIR *dir_ptr;
    struct dirent *direntp;
    if((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr,"ls1:cannot open %s \n",dirname);
    else
    {
        while( (direntp = readdir(dir_ptr)) != NULL)
            dostat(direntp->d_name);
        closedir(dir_ptr);
    }
    
}
void dostat(char *filename){
     struct stat info;
     if(stat(filename,&info) != -1){
            show_stat_info(filename,&info);
        }
        else
        {
            perror(filename);
        }
        
}

void show_stat_info(char *fname,struct stat *buf){
    char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters(buf->st_mode,modestr);

    printf("    mode    :   %s\n",modestr);
    printf("    links   :   %d\n",buf->st_nlink);
    printf("    user    :   %s\n",uid_to_name(buf->st_uid));
    printf("    group   :   %s\n",gid_to_name(buf->st_gid));
    printf("    size    :   %d\n",buf->st_size);
    printf("    modtime :   %s",4+ctime(&buf->st_mtime));
    printf("    name    :   %s\n",fname);
}
void mode_to_letters(int mode,char str[])
{
    strcpy(str,"----------");
    if(S_ISDIR(mode))str[0]='d';
    if(S_ISCHR(mode))str[0]='c';
    if(S_ISBLK(mode))str[0]='b';
    if(mode&S_IRUSR)str[1]='r';
    if(mode&S_IWUSR)str[2]='w';
    if(mode&S_IXUSR)str[3]='x';
    if(mode&S_IRGRP)str[4]='r';
    if(mode&S_IWGRP)str[5]='w';
    if(mode&S_IXGRP)str[6]='x';
    if(mode&S_IROTH)str[7]='r';    
    if(mode&S_IWOTH)str[8]='w';
    if(mode&S_IXOTH)str[9]='x';

}

char *uid_to_name(uid_t uid){
    struct passwd *getpwuid(),*pw_ptr;
    static char numstr[10];
    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr,"%d",uid);
        return numstr;
    }
    else
    {
        return pw_ptr->pw_name;
    }
    
}
char *gid_to_name(gid_t gid){
    struct group *getgrgid(),*grp_ptr;
    static char numstr[10];

    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr,"%d",gid);
        return numstr;
    }
    else
    {
        return grp_ptr->gr_name;
    }
    
}