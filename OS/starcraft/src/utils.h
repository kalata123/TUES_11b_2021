#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>

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

//TODO:
void pause_scv(pthread_mutex_t *);
void resume_scv(pthread_mutex_t *);
void cancel_threads(pthread_mutex_t *);
void run_threads(pthread_mutex_t *);

#endif // !UTILS_H