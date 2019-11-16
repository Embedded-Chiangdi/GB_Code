// #include <stdio.h>
// void someFunction(int arg)
// {
//     printf("This is someFunction being called and arg is: %d\n", arg);
//     printf("Whoops leaving the function now!\n");
// }

// main()
// {
//     void (*pf)(int);
//     pf = &someFunction;
//     //printf("%p\n",pf);
//     //printf("%p\n",&someFunction);
//     //printf("We're about to call someFunction() using a pointer!\n");
//     (pf)(5);
//     //printf("Wow that was cool. Back to main now!\n\n");
// }
#include <stdio.h>
int add(int a, int b){
    return a+b;
}

int main(int argc, char*argv[]){
    int (*fp)(int , int)=&add;
    int sum=0;

    sum=(*fp)(3,6);
    printf("3 + 6 = %d\n",sum);

    return 0;
}