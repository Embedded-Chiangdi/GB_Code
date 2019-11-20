#include <stdio.h>
const int test(const int a, const int b);
static const char *test_string(const char *str);
int main()
{
    char buf[]="This is a test";
    printf("Before test_string is %s \n",buf);
    printf("After test_string is %s \n",test_string(buf));
    //int b;
    //b=test(5,6);
    //b=7;
    //printf("b = %d\n",b);
}
static const char *test_string(const char *str){
    //str++;
    //strcpy(str,"changed");
    str[1]='/0';
    return str; 
}
const int test(const int a , int b)
{
   // a=10;
    b=10;
    printf("a + b = %d\n",a+b);
    return a+b;
}