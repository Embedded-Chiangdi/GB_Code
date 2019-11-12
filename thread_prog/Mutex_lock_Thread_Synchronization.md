## Mutex lock for Linux Thread Synchronization
Thread synchronization is defined as a mechanism which ensures that two or more concurrent processes or threads do not simultaneously execute some particular program segment known as critical section.Processes’ access to critical section is controlled by using synchronization techniques.  
An example code of synchronization problems:
```
#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 

pthread_t tid[2]; 
int counter; 

void* trythis(void *arg) 
{ 
	unsigned long i = 0; 
	counter += 1; 
	printf("\n Job %d has started\n", counter); 

	for(i=0; i<(0xFFFFFFFF);i++); 
	printf("\n Job %d has finished\n", counter); 

	return NULL; 
} 

int main(void) 
{ 
	int i = 0; 
	int error; 

	while(i < 2) 
	{ 
		error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
		if (error != 0) 
			printf("\nThread can't be created : [%s]", strerror(error)); 
		i++; 
	} 

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 

	return 0; 
} 
```
The output is 
```
[jiangdi@example thread_prog]$ ./a.out

 Job 1 has started

 Job 2 has started

 Job 2 has finished

 Job 2 has finished

```
From the output we can see that the log `Job 2 has finished` is repeated twice.

### Refer
* [Mutex lock for Linux Thread Synchronization](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
* [pthread_mutex_lock](https://linux.die.net/man/3/pthread_mutex_lock)
* [pthread_mutex_lock](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/ptmlock.htm)
* [Mutex lock threads](https://stackoverflow.com/questions/14888027/mutex-lock-threads)