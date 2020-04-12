#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SOLDIER_COST 50
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
    // printf("ъъъЪ?...\n");
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

int canMine(int *mineral, int MINERALS, pthread_mutex_t *mutex) {
    mutex_lock(mutex);
    if (*mineral < MINERALS) {
        mutex_unlock(mutex);
        return 1;
    }
    mutex_unlock(mutex);
    return 0;
}

int hasMinerals(int MINERAL_BLOCKS, int MINERALS, pthread_mutex_t *mineral_block_mutexes, int *mineral_blocks) {
    for (int i = 0; i < MINERAL_BLOCKS; ++i) {
        mutex_lock(&mineral_block_mutexes[i]);
        if (mineral_blocks[i] < MINERALS) {
            mutex_unlock(&mineral_block_mutexes[i]);
            return 1;
        } else {
            mutex_unlock(&mineral_block_mutexes[i]);
        }
    }
    return 0;
}

void create_soldier(int *cc_minerals,
                    int *soldiers) {
    *cc_minerals -= SOLDIER_COST;
    sleep(1);
    *soldiers += 1;
    printf("You wanna piece of me, boy?\n");
}

void pause_scv(pthread_mutex_t *mutex,
               int *paused) {
    mutex_lock(mutex);
    *paused = 1;
}

void resume_scv(pthread_mutex_t *mutex,
                int *paused) {
    *paused = 0;
    mutex_unlock(mutex);
}

void cancel_thread(pthread_t thread) {
    pthread_cancel(thread);
}

void run_threads(pthread_t thread,
                 void *(*scv)(void *),
                 long id) {
    create_thread(&thread, NULL, scv, (void *)id);
}

void check_pause(int *paused) {
    while (*paused)
        ;
}

void signal_scv(scv_t *scv) {
    *scv->signal_stop = !*scv->signal_stop;
}

void mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr) {
    if (pthread_mutex_init(mutex, attr) != 0) {
        perror("Initializing mutex");
        pthread_exit(NULL);
        exit(0);
    }
}

void mutex_destroy(pthread_mutex_t *mutex) {
    if (pthread_mutex_destroy(mutex) != 0) {
        perror("Destroying mutex");
        pthread_exit(NULL);
        exit(0);
    }
}