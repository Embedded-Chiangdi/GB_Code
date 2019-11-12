#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sharedResource = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* fooAPI(void* param)
{
    pthread_mutex_lock(&mutex);
    printf("Enter this thread\n");
    printf("Before change the sharedResource is %d\n",sharedResource);
    printf("Changing the shared resource now.\n");
    sharedResource = 42;
    pthread_mutex_unlock(&mutex);
    //return 0;
}

int main()
{
    pthread_t thread;
    // Really not locking for any reason other than to make the point.
    pthread_mutex_lock(&mutex);
    printf("Create this thread\n");
    pthread_create(&thread, NULL, fooAPI, NULL);
    sleep(1);
    pthread_mutex_unlock(&mutex);

    // Now we need to lock to use the shared resource.
    pthread_mutex_lock(&mutex);
    printf("Main.c 31 = %d\n", sharedResource);
    pthread_mutex_unlock(&mutex);
    sleep(10);
    printf("Main.c 34 = %d\n", sharedResource);
    //return 0;
}