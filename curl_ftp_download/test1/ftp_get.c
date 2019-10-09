#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <unistd.h>
struct FtpFile {
  const char *filename;
  FILE *stream;
};
 
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
 
 
int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile = {
    "get.txt", /* name to store the file as if successful */ 
    NULL
  };
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    /*
 *      * You better replace the URL with one that works!
 *           */ 
    curl_easy_setopt(curl, CURLOPT_URL,
                     "ftp://10.60.119.200/get.txt");
    curl_easy_setopt(curl,CURLOPT_USERPWD,"testftp:testftp");
    /* Define our callback to get called when there's data to be written */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */ 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
 
    /* Switch on full protocol/debug output */ 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    if(CURLE_OK != res) {
      /* we failed */ 
      fprintf(stderr, "curl told us %d\n", res);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */ 
 
  curl_global_cleanup();
 
  return 0;
}
