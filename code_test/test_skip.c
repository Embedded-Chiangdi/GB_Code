#include <stdio.h>
static const char *skip(const char *in);
int main()
{
    char text[]="  {\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    printf("Before skip:\n%s\n",text);
    printf("After skip:\n%s\n",skip(text));
    return 0;

}
static const char *skip(const char *in)
 {
     while (in && *in && (unsigned char)*in<=32) 
                in++; 
     return in;
     }