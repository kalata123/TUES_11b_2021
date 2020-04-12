#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

//struct for all variables needed by each the scv
typedef struct {
    int *id;
    pthread_mutex_t *mutex;
    pthread_t *thread;
    int *signal_stop;
} scv_t;

/* helpful functions for mutexes */
int mutex_trylock(pthread_mutex_t *);
void mutex_lock(pthread_mutex_t *);
void mutex_unlock(pthread_mutex_t *);

/* helpful functions for threads */
void join_thread(pthread_t *, void *);

void create_thread(pthread_t *thread,
                   const pthread_attr_t *thread_attr,
                   void *(*func)(void *),
                   void *func_attr);
int canMine(int *mineral,
            int MINERALS,
            pthread_mutex_t *mutex);

int hasMinerals(int MINERAL_BLOCKS,
                int MINERALS,
                pthread_mutex_t *mineral_block_mutexes,
                int *mineral_blocks);
void create_soldier(int *cc_minerals,
                    int *soldiers);

void pause_scv(pthread_mutex_t *mutex,
               int *paused);

void resume_scv(pthread_mutex_t *mutex,
                int *paused);

void cancel_thread(pthread_t thread);

void run_threads(pthread_t thread,
                 void *(*scv)(void *),
                 long id);
void check_pause(int *);

void signal_scv(scv_t *scv);

void mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t * attr);

void mutex_destroy(pthread_mutex_t *mutex);
#endif // !UTILS_H
