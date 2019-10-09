#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct FtpFile{
    char *filename;
    FILE *stream;
  };

char * del_left_trim(char *str);
char * del_both_trim(char * str);
int read_one_para(FILE *fp,char *t_buf);
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);
int myf_ftp_download(char *ftp_remote_path,char *user_passwd,char*downlod_local_path);

