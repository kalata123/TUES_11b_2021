#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

/*
Some global variables that DO NOT change during the runtime
*/
#define MAX_UNITS 200 // scvs + soldiers <= 200
#define MINERALS 500  // minerals in each mineral block
#define SOLDIERS 20   // needed soldiers to finish the game

/* refactor using __sync_add_and_fetch type funcs */

/* Some global variables that DO change during the runtime s*/
int MINERAL_BLOCKS = 2, // default total mineral blocs
    soldiers = 0;       // need 20 to win

/* SCV variables. Second is for dynamic memmory */
long scvs = 5; // workers that dig minerals
long SCV_CAPACITY = 10;

/* variables for the mineral blocks on the map */
int *mineral_blocks = NULL;
pthread_mutex_t *mineral_block_mutexes = NULL;

int cc_minerals = 0; // + soldiers*50 + (scv-5{initial scv don't count})*50 == MINERAL_BLOCKS * MINERALS
pthread_mutex_t cc_minerals_mutex;

// pthread_t        scv_threads[MAX_UNITS]; /* TODO: make it dynamic memmory*/
pthread_t *scv_threads = NULL;
/* mutex for dynamic set of SCVs */
pthread_mutex_t *scvs_mutexes = NULL;

/* functions to be run on additional threads */
void *scv(void *id);
void *user_input();

/* helping functions for cleaner code */
void create_soldier();
void create_scv();
int hasMinerals();
int canMine(int *, pthread_mutex_t *);

/* helpful functions for beginning and ending of program */
void init(int, char **);
void outit();

void get_additional_memmory();

int main(int argc, char *argv[]) {

    /* init mutexes, set dynamic memmory and console args */
    init(argc, argv);
    /* creating threads for initial SCVs */
    for (long scv_count = 0; scv_count < 5; ++scv_count) {
        printf("hmm...\n");
        create_thread(&scv_threads[scv_count], NULL, scv, (void *)(scv_count + 1));
        // printf("%p\n", &scv_threads[scv_count]);
    }

    /* creating thread explicitly for user input  */
    pthread_t userInput;
    create_thread(&userInput, NULL, user_input, NULL);

    /* waiting for all soldiers to be completed */
    join_thread(&userInput, NULL);

    /* waiting for all minerals to be mined */
    for (int i = 0; i < scvs; ++i) {
        join_thread(&scv_threads[i], NULL);
    }

    /* before the end printing the state of the game */
    printf("Map minerals %d, player minerals %d, SCVs %ld, Marines %d\n",
           MINERAL_BLOCKS * MINERALS, cc_minerals, scvs, soldiers);

    /* destroy mutexes and free memmory*/
    outit();

    return 0;
}

void *scv(void *id) {
    // Step 6 - over again
    while (hasMinerals()) {
        mutex_lock(&scvs_mutexes[(long)id]);
        printf("%ld locked mutex...\n", (long)id);
        for (int i = 0; i < MINERAL_BLOCKS; ++i) {
            sleep(3);
            // Step 2 - check if mineral block is empty
            if (canMine(&mineral_blocks[i], &mineral_block_mutexes[i])) { // !0 == true
                // Step 3 - dig minerals - 0 sec
                if (mutex_trylock(&mineral_block_mutexes[i])) {
                    printf("SCV %ld is mining from mineral block %d\n", (long)id, i + 1);
                    int taken_minerals = (mineral_blocks[i] >= MINERALS - 8) ? MINERALS - mineral_blocks[i] : 8; // should be out of sycle - used in another place, too
                    mineral_blocks[i] += taken_minerals;
                    mutex_unlock(&mineral_block_mutexes[i]);
                    // Step 4 - transporting 2 sec
                    printf("SCV %ld is transporting minerals\n", (long)id);
                    sleep(2);
                    // Step 5 - delivering 0 sec;
                    mutex_lock(&cc_minerals_mutex);
                    cc_minerals += taken_minerals;
                    mutex_unlock(&cc_minerals_mutex);
                    printf("SCV %ld delivered minerals to the Command center\n", (long)id);
                }
            }
        }
        mutex_unlock(&scvs_mutexes[(long)id]);
    }
    return NULL;
}

void *user_input() {
    char ch;
    while (1) {
        if (scanf("%c", &ch) == EOF) {
            perror("Scanf error");
            pthread_exit(NULL);
            exit(0);
        }
        switch (ch) {
        case 'm':
            if (scvs + soldiers < MAX_UNITS) {
                mutex_lock(&cc_minerals_mutex);
                if (cc_minerals >= 50)
                    create_soldier();
                else
                    printf("Not enough minerals.\n");
                mutex_unlock(&cc_minerals_mutex);
                if (soldiers >= SOLDIERS) {
                    return NULL;
                }
            }
            break;
        case 's':
            if (scvs + soldiers < MAX_UNITS) {
                mutex_lock(&cc_minerals_mutex);
                if (cc_minerals >= 50)
                    create_scv();
                else
                    printf("Not enough minerals.\n");
                mutex_unlock(&cc_minerals_mutex);
            }
            break;
        case 'q':
            break;
        }
    }
}

void create_soldier() {
    cc_minerals -= 50;
    sleep(1);
    soldiers += 1;
    printf("You wanna piece of me, boy?\n");
}

void create_scv() {
    cc_minerals -= 50;
    if (scvs >= SCV_CAPACITY)
        get_additional_memmory();
    sleep(1);
    create_thread(&scv_threads[scvs], NULL, scv, (void *)(scvs + 1));
    ++scvs;
    printf("SCV good to go, sir.\n");
}

int hasMinerals() {
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

int canMine(int *mineral, pthread_mutex_t *mutex) {
    mutex_lock(mutex);
    if (*mineral < MINERALS) {
        mutex_unlock(mutex);
        return 1;
    }
    mutex_unlock(mutex);
    return 0;
}

void init(int argc, char *argv[]) {
    if (argc >= 2) {
        MINERAL_BLOCKS = atoi(argv[1]);
    }
    scv_threads = (pthread_t *)malloc(scvs * sizeof(pthread_t));
    scvs_mutexes = (pthread_mutex_t *)malloc(SCV_CAPACITY * sizeof(pthread_mutex_t));
    mineral_blocks = (int *)realloc(mineral_blocks, sizeof(int) * MINERAL_BLOCKS);
    mineral_block_mutexes = (pthread_mutex_t *)realloc(mineral_block_mutexes, sizeof(pthread_mutex_t) * MINERAL_BLOCKS);
    memset(mineral_blocks, 0, MINERAL_BLOCKS * sizeof(int));

    for (int i = 0; i < SCV_CAPACITY; ++i) {
        if (pthread_mutex_init(&scvs_mutexes[i], NULL) != 0) {
            perror("Initializing mineral mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }

    for (int i = 0; i < MINERAL_BLOCKS; ++i) {
        if (pthread_mutex_init(&mineral_block_mutexes[i], NULL) != 0) {
            perror("Initializing mineral mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }
    if (pthread_mutex_init(&cc_minerals_mutex, NULL) != 0) {
        perror("Initializing Command center minerals mutex");
        pthread_exit(NULL);
        exit(0);
    }
}

void outit() {
    for (int i = 0; i < MINERAL_BLOCKS; ++i) {
        if (pthread_mutex_destroy(&mineral_block_mutexes[i]) != 0) {
            perror("Destroying mineral minerals mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }

    if (pthread_mutex_destroy(&cc_minerals_mutex) != 0) {
        perror("Destroying Command center minerals mutex");
        pthread_exit(NULL);
        exit(0);
    }

    for (int i = 0; i < SCV_CAPACITY; ++i) {
        if (pthread_mutex_destroy(&scvs_mutexes[i]) != 0) {
            perror("Destroying mineral minerals mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }

    free(mineral_blocks);
    free(mineral_block_mutexes);
    free(scv_threads);
}

void get_additional_memmory() {
    // lock for every scv
    for (int i = 0; i < SCV_CAPACITY; i++) {
        printf("%p\n", (void *)&scvs_mutexes[i]);
        sleep(2);
        printf("Mutex for %d scv locking...\n", i + 1);
        mutex_lock(&scvs_mutexes[i]);
        printf("Mutex for %d scv locked...\n", i + 1);
    }

    for (int i = 0; i < SCV_CAPACITY; ++i)
        pthread_cancel(scv_threads[i]);

    // realloc all scvs
    scv_threads = (pthread_t *)realloc(scv_threads, (SCV_CAPACITY * 2) * sizeof(pthread_t));

    // recreate threads
    for (long i = 0; i < SCV_CAPACITY; ++i)
        create_thread(&scv_threads[i], NULL, scv, (void *)(i + 1));

    // unlock for every scv
    for (int i = 0; i < SCV_CAPACITY; i++)
        mutex_unlock(&scvs_mutexes[i]);

    SCV_CAPACITY *= 2;
    scvs_mutexes = (pthread_mutex_t *)realloc(scvs_mutexes, SCV_CAPACITY * sizeof(pthread_mutex_t));

    for (int i = SCV_CAPACITY / 2; i < SCV_CAPACITY; ++i) {
        if (pthread_mutex_init(&scvs_mutexes[i], NULL) != 0) {
            perror("Initializing mineral mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }
}
