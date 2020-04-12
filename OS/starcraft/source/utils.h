//--------------------------------------------
// NAME: Kaloyan Angelov
// CLASS: Xib
// NUMBER: 15
// PROBLEM: #3
// FILE NAME: utils.h
// FILE PURPOSE: Header file for utils.c
//---------------------------------------------
#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

/* structure for everything the game would need from a
     SCV during the game */
typedef struct {
    int *id;
    pthread_mutex_t *mutex;
    pthread_t *thread;
    int *signal_stop;
} scv_t;

/* helpful functions for mutexes basically same as original
    but can  also handle errors */
int mutex_trylock(pthread_mutex_t *);
void mutex_lock(pthread_mutex_t *);
void mutex_unlock(pthread_mutex_t *);
void mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr);
void mutex_destroy(pthread_mutex_t *mutex);

/* helpful functions for threads */
void join_thread(pthread_t *, void *);
void create_thread(pthread_t *thread,
                   const pthread_attr_t *thread_attr,
                   void *(*func)(void *),
                   void *func_attr);

/* checker functions */
int canMine(int *mineral,
            int MINERALS,
            pthread_mutex_t *mutex);

int hasMinerals(int MINERAL_BLOCKS,
                int MINERALS,
                pthread_mutex_t *mineral_block_mutexes,
                int *mineral_blocks);

/* helping function for creating soldier */
void create_soldier(int *cc_minerals,
                    int *soldiers);

/* some stuff for synchronizing dynamic reallocation of threads*/
void signal_scv(scv_t *scv);

#endif // !UTILS_H
