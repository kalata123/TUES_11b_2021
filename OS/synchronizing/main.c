#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

#define SHOFERI 20
#define CARS 5

// typedef struct
// {
//     int cars[5][2];
// } shofer_t;

pthread_mutex_t cars_mutex[CARS];

void *tryCar(void *shof){
    long shofer = (long) shof;
    while (1)
    {
        for (int i = 0; i < CARS; ++i){
            if (pthread_mutex_trylock(&cars_mutex[i]) == 0){
                printf("Buyer %ld takes car %d.\n", shofer, i+1);
                if (pthread_mutex_unlock(&cars_mutex[i]) != 0){
                    perror("Unlock failed");
                }
                printf("Buyer %ld returns car %d.\n", shofer, i+1);
                return NULL;
            }
        }
    }
}

int main() {
    // shofer_t shofers[SHOFERI];
    pthread_t threads[SHOFERI];

    for (int i = 0; i < CARS; ++i){
        if (pthread_mutex_init(&cars_mutex[i], NULL) != 0){
            perror("car_1 mutex init");
        }
    }


    for (long i = 0; i < SHOFERI; ++i){
        if (pthread_create(&threads[i], NULL, tryCar, (void *)(i+1)) == -1){
            perror("pthread_create error");
        }
    }

    for (long i = 0; i < SHOFERI; ++i){
        if (pthread_join(threads[i], NULL) == -1){
            perror("pthread_create error");
        }
    }

    for (int i = 0; i < CARS; ++i){
        if (pthread_mutex_destroy(&cars_mutex[i]) != 0){
            perror("car_1 mutex destroy");
        }
    }

    return 0;
}