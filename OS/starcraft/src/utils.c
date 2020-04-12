#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mutex_trylock(pthread_mutex_t *mutex) {
    if (pthread_mutex_trylock(mutex)) {
        return 0;
    } else {
        return 1;
    }
}

void mutex_lock(pthread_mutex_t *mutex) {
    int retcode;
    if ((retcode = pthread_mutex_lock(mutex))) {
        // perror("Mutex lock");
        printf("Mutex lock %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
        printf("ъъъЪ?...\n");
}

void mutex_unlock(pthread_mutex_t *mutex) {
    if (pthread_mutex_unlock(mutex)) {
        perror("Mutex unlock");
        pthread_exit(NULL);
        exit(0);
    }
}

void join_thread(pthread_t *thread, void *ret) {
    if (pthread_join(*thread, ret)) {
        perror("Joining error");
        pthread_exit(NULL);
        exit(0);
    }
}

void create_thread(pthread_t *thread, const pthread_attr_t *thread_attr, void *(*func)(void *), void *func_attr) {
    if (pthread_create(thread, thread_attr, func, func_attr)) {
        perror("Create thread");
        pthread_exit(NULL);
        exit(0);
    }
}