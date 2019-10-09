#include "ftp_file_get.h"

int main(int argc, char * argv[])
{
  FILE *fp=NULL;
  char t_buf[80];
  char ftp_path[80];
  char local_path[80];
  char user_p[20];
  char i;
  /* check our argument */
  if(2 != argc)
    {
      printf("Usage: ./ftp_get <configuration files path>\n");
      return 1;
    }
      
  /* read our configuration files*/
  fp= fopen(argv[1],"r");
  
  
  read_one_para(fp,t_buf);
  strncpy(ftp_path,t_buf,sizeof(ftp_path));


  read_one_para(fp,t_buf);
  strncpy(user_p,t_buf,sizeof(user_p));


  read_one_para(fp,t_buf);
  strncpy(local_path,t_buf,sizeof(local_path));
  fclose(fp);
  i=strlen(ftp_path);
  ftp_path[i-1]='\0';
  i=strlen(user_p);
  user_p[i-1]='\0';
  i=strlen(local_path);
  local_path[i-1]='\0';
  printf("LOACL_PATH=%s",local_path);
  printf("\nFTP_PATH=%s",ftp_path);
  printf("\nADMIN=%s",user_p);
  sleep(10);
  myf_ftp_download(ftp_path,user_p,local_path);
 
  return 0;    
}
int read_one_para(FILE *fp,char *t_buf)
{
    char buf[100];
    char *p,ch;
     while (!feof(fp)) {
       //memset(buf, 0, sizeof(t_buf));
       memset(buf, 0, sizeof(buf));
        if ((fgets(buf, sizeof(buf), fp)) != NULL) {
            ch=del_left_trim(buf)[0];
           /*判断注释 空行，如果是就直接下次循环*/
            if (ch == '#' || isblank(ch) || ch=='\n')
                continue;
            /*分割字符串*/
            strtok(buf, "=");
            p=strtok(NULL, "=");
            strcpy(t_buf,p);
          /*如果不是注释，空行，就读取到一个参数，然后终止循环*/
        }
        break;
    }
  return 0;
}


/*   删除左边的空格   */
char * del_left_trim(char *str) {
    
    assert(str != NULL);
    for (;*str != '\0' && isblank(*str) ; ++str);

    return str;
}
/*   删除两边的空格   */
char * del_both_trim(char * str) {
    char *p;
    char * szOutput;

    szOutput = del_left_trim(str);
    for (p = szOutput + strlen(szOutput) - 1; p >= szOutput && isblank(*p);--p);
    *(++p) = '\0';

    return szOutput;
}
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
	struct FtpFile *out = (struct FtpFile *)stream;
		if(!out->stream) {
    		/* open file for writing */ 
    		out->stream = fopen(out->filename, "wb");
    		if(!out->stream)
      		return -1; /* failure, can't open file to write */ 
  		}
  	return fwrite(buffer, size, nmemb, out->stream);
}

int myf_ftp_download(char *ftp_remote_path,char *user_passwd,char*downlod_local_path)
{

  CURL *curl;
  CURLcode res;
  struct FtpFile my_ftpfile = {
    "0", /* name to store the file as if successful */ 
    NULL
  };

  //load our name to store the file as if successful
  strncpy(my_ftpfile.filename,downlod_local_path,sizeof(my_ftpfile.filename));
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {

      curl_easy_setopt(curl, CURLOPT_URL,ftp_remote_path);
      curl_easy_setopt(curl,CURLOPT_USERPWD,user_passwd);
      /* Define our callback to get called when there's data to be written */ 
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
      /* Set a pointer to our struct to pass to the callback */ 
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_ftpfile);
      /* Switch on full protocol/debug output */ 
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
      res = curl_easy_perform(curl);
      /* always cleanup */ 
      curl_easy_cleanup(curl);

      if(CURLE_OK != res) 
      {
        /* we failed */ 
          fprintf(stderr, "curl told us %d\n", res);
      }
  }
 
  if(my_ftpfile.stream)
    fclose(my_ftpfile.stream); /* close the local file */ 
 
  curl_global_cleanup();
 
  return 0;
}

