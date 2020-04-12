//--------------------------------------------
// NAME: Kaloyan Angelov
// CLASS: Xib
// NUMBER: 15
// PROBLEM: #3
// FILE NAME: utils.c
// FILE PURPOSE:
// Source file for some helpful functions outside main file
//---------------------------------------------
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SOLDIER_COST 50

int mutex_trylock(pthread_mutex_t *mutex) {
    //--------------------------------------------
    // FUNCTION: mutex_trylock
    // pthread_mutex_trylock with error handling
    // PARAMETERS:
    // *mutex - pointer to a mutex that has to be trylocked
    //----------------------------------------------
    if (pthread_mutex_trylock(mutex)) {
        return 0;
    } else {
        return 1;
    }

    return 1;
}

void mutex_lock(pthread_mutex_t *mutex) {
    //--------------------------------------------
    // FUNCTION: mutex_lock
    // pthread_mutex_lock with error handling
    // PARAMETERS:
    // *mutex - pointer to a mutex that has to be locked
    //----------------------------------------------
    int retcode;
    if ((retcode = pthread_mutex_lock(mutex))) {
        printf("Mutex lock %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
    // printf("ъъъЪ?...\n");
}

void mutex_unlock(pthread_mutex_t *mutex) {
    //--------------------------------------------
    // FUNCTION: mutex_unlock
    // pthread_mutex_unlock with error handling
    // PARAMETERS:
    // *mutex - pointer to a mutex that has to be unlocked
    //----------------------------------------------
    int retcode;
    if ((retcode = pthread_mutex_unlock(mutex))) {
        printf("Mutex unlock %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
}

void join_thread(pthread_t *thread, void *ret) {
    //--------------------------------------------
    // FUNCTION: join_thread
    // pthread_join with error handling
    // PARAMETERS:
    // *thread - pointer to the thread to be joined
    // *ret - retval of pthread_join
    //----------------------------------------------
    int retcode;
    if ((retcode = pthread_join(*thread, ret))) {
        printf("Pthread join %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
}

void create_thread(pthread_t *thread,
                   const pthread_attr_t *thread_attr,
                   void *(*func)(void *),
                   void *func_attr) {
    //--------------------------------------------
    // FUNCTION: create_thread
    // pthread_join with error handling
    // PARAMETERS:
    // *thread - pointer to the thread to be created
    // const pthread_attr_t *thread_attr - thread attributes
    // void *(*func)(void *) - function to be executed
    // void *func_attr - attributes for functions
    //----------------------------------------------
    int retcode;
    if ((retcode = pthread_create(thread, thread_attr, func, func_attr))) {
        printf("Pthread create %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
}

int canMine(int *mineral, int MINERALS, pthread_mutex_t *mutex) {
    //--------------------------------------------
    // FUNCTION: canMine
    // pthread_join with error handling
    // PARAMETERS:
    // int *mineral - mineral block to be checked
    // int MINERALS - reference to initial minerals
    // pthread_mutex_t *mutex - mutex to lock while checking
    //----------------------------------------------
    mutex_lock(mutex);
    if (*mineral < MINERALS) {
        mutex_unlock(mutex);
        return 1;
    }
    mutex_unlock(mutex);
    return 0;
}

int hasMinerals(int MINERAL_BLOCKS,
                int MINERALS,
                pthread_mutex_t *mineral_block_mutexes,
                int *mineral_blocks) {
    //--------------------------------------------
    // FUNCTION: hasMinerals
    // checks if left any minerals
    // PARAMETERS:
    // int MINERAL_BLOCKS - total count of mineral blocks
    // int MINERALS - reference to initial minerals 
    // pthread_mutex_t *mineral_block_mutexes - mutex to be locked 
    //                      while working with the mineral block
    // int *mineral_blocks - mineral blocks to be checked
    //----------------------------------------------
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
    //--------------------------------------------
    // FUNCTION: create_soldier
    // creates new marine
    // PARAMETERS:
    // int *cc_minerals - total minerals to be substracted
    // int *soldiers - marines to be incremented
    //----------------------------------------------
    *cc_minerals -= SOLDIER_COST;
    sleep(1);
    *soldiers += 1;
    printf("You wanna piece of me, boy?\n");
}

void signal_scv(scv_t *scv) {
    //--------------------------------------------
    // FUNCTION: signal_scv
    // signals the scv to stop its routine
    // PARAMETERS:
    // scv_t *scv - the scv to be notified
    //----------------------------------------------
    *scv->signal_stop = !*scv->signal_stop;
}

void mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr) {
    //--------------------------------------------
    // FUNCTION: mutex_init
    // pthread_mutex_init with error handling
    // PARAMETERS:
    // pthread_mutex_t *mutex - mutex to be initialized
    // pthread_mutexattr_t *attr - mutex attributes
    //----------------------------------------------
    int retcode;
    if ((retcode = pthread_mutex_init(mutex, attr) != 0)) {
        printf("Pthread mutex init %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
}

void mutex_destroy(pthread_mutex_t *mutex) {
    //--------------------------------------------
    // FUNCTION: mutex_destroy
    // pthread_mutex_destroy with error handling
    // PARAMETERS:
    // pthread_mutex_t *mutex - mutex to be destroyed
    //----------------------------------------------
    int retcode;
    if ((retcode = pthread_mutex_destroy(mutex) != 0)) {
        printf("Pthread mutex destroy %s\n", strerror(retcode));
        pthread_exit(NULL);
        exit(0);
    }
}