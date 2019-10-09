#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct FtpFile{
    const char *filename;
    FILE *stream;
  };

char * del_left_trim(char *str);
char * del_both_trim(char * str);
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);
int myf_ftp_download(int argc, char *argv[]);

