## Function Pointer In C
I would have expected to make an summary of explanation of how "function pointers work", not how they are coded :) Here We go !
***
In C, like normal data pointers (int *, char *, etc), we can have pointers to functions. By definition that pointers point to an address in any memory location,function pointer points to the beginning address of the executable code as functions in memory. Besides, Unlike normal pointers, we do not allocate de-allocate memory using function pointers.
***
### What ie Point Of Function Pointers?
* Callbacks 
> used for event handlers, parser specialization, comparator function passing, different patterns ...

* API Pack (like cjson_malloc)
>To allow programmers to use libraries for different usages -> "Flexibility"

***
### Function Pointer Syntax 
```
char (*pf)(int , int)
```
This definitely is very complicated, Let's re-read this code and understand it point by point. ` *pf ` is the  pointer to a function. ` char ` is the return type of that function, and finally ` int ` are the argument type of that function.  
If you insert a `*` before the function pointer and it become follow:
```
char* (*pf)(int , int)
``` 
we read this point by point again. ` char* ` is return type of the function.` *pf ` is the  pointer to a function. ` char ` is the return type of that function, and finally ` int ` are the argument type of that function.  
That is the difference between `函数指针` and `指针函数`. Honestly, I always confussed with chinese explanations of this diff. English explanation seems much easier. 
***
### Examples
Let's get our hands dirty with some real code. See this example:
```c
#include <stdio.h>
int add(int a, int b){
    return a+b;
}

int main(int argc, char*argv[]){
    int (*fp)(int , int)=&add;
    int sum=0;

    sum=(*fp)(3,6);
    printf("3 + 6 = %d",sum);

    return 0;
}
```
The output is: 
```
[jiangdi@example code_test]$ gcc test_fun_pointer.c 
[jiangdi@example code_test]$ ./a.out 
3 + 6 = 9
```
***
### Interesting Facts about function pointers
A function’s name can also be used to get functions’ address. For example, in the below program, we have removed address operator ‘&’ in assignment. We have also changed function call by removing *, the program still works.
```c
#include <stdio.h>
int add(int a, int b){
    return a+b;
}

int main(int argc, char*argv[]){
    int (*fp)(int , int)=&add;
    //another way is follow
    //int (*fp)(int , int)=add;
    int sum=0;

    //sum=(*fp)(3,6)
    sum=fp(3,6);
    printf("3 + 6 = %d",sum);

    return 0;
}
```
The output is: 
```
[jiangdi@example code_test]$ gcc test_fun_pointer.c 
[jiangdi@example code_test]$ ./a.out 
3 + 6 = 9
```
After I search a lot in internet, I figure it out.
>So `fp` is the pointer, and `*fp` is the function, and `(*fp)()` is the logical way to call it. But since there's not much you can do with a function pointer except call it, when you write `fp()`, without the *, the compiler (for once in its tiny, narrow-minded life) says, "Oh, okay, I guess you're trying to call the pointed-to function, so that's what we'll do."  `fp` in this context is converted to the address of the function.


### Reference Reading
* [Function Pointer in C](https://www.geeksforgeeks.org/function-pointer-in-c/)
* [How to declare a pointer to a function?](https://www.geeksforgeeks.org/how-to-declare-a-pointer-to-a-function/)
* [How to declare a pointer to a function?](https://www.geeksforgeeks.org/how-to-declare-a-pointer-to-a-function/)
* [How do function pointers in C work?](https://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work)
* [c function pointers](https://www.guru99.com/c-function-pointers.html)
* [The Ksplice Pointer Challenge](https://blogs.oracle.com/linux/the-ksplice-pointer-challenge-v2)
* [How do pointer to pointers work in C?](https://stackoverflow.com/questions/897366/how-do-pointer-to-pointers-work-in-c/897414#897414)
* [Invoke function using pointer to function in C](https://stackoverflow.com/questions/46022330/invoke-function-using-pointer-to-function-in-c)
* [Function Pointers in C](https://cs.nyu.edu/courses/spring12/CSCI-GA.3033-014/Assignment1/function_pointers.html)
* [14.3 Pointers to Functions](http://www-ee.eng.hawaii.edu/~tep/EE150/book/chap14/section2.1.3.html)
* [Function Pointers](https://www.learn-c.org/en/Function_Pointers)
* [Why point to a function](https://stackoverflow.com/questions/2592137/what-is-the-point-of-function-pointers)
* [How do function pointers in C work?](https://stackoverflow.com/questions/840501/how-do-function-pointers-in-c-work)
***
