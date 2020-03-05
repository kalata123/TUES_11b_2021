#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#define NUMBER_OF_THREADS 5 

void * printHello(void* arg){
    long thread_id = (long)arg;
    printf("hello from thread %ld \n", thread_id);
    return (void*)(thread_id*thread_id);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];
    void* retval;//[NUMBER_OF_THREADS];
    for (long i = 0; i < NUMBER_OF_THREADS; i++){
        if (pthread_create(&threads[0], NULL, printHello, (void *)i) == -1){
            perror("pthread create");
            return 1;
        }
        if (pthread_join(threads[0], &retval) == -1){
            perror("pthread_join");
            return 2;
        }
        long retval_l = (long)retval;
        printf("ret val of thread %ld is %ld\n", i, retval_l);
    }
    for (long i = 0; i < NUMBER_OF_THREADS; ++i){
    }
        
    printf("hello world\n");
    return 0;
}
