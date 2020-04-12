#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Some global variables that DO NOT change during the runtime
*/
#define MAX_UNITS 200 // scvs + soldiers <= 200
#define MINERALS 500  // minerals in each mineral block
#define SOLDIERS 20    // needed soldiers to finish the game
#define SCV_COST 50
#define SOLDIER_COST 50

/* refactor using __sync_add_and_fetch type funcs */

/* Some global variables that DO change during the runtime s*/
int MINERAL_BLOCKS = 2, // default total mineral blocs
    soldiers = 0;       // need 20 to win

/* SCV variables. Second is for dynamic memory */
long scvs = 5; // workers that dig minerals
long SCV_CAPACITY = 10;

/* variables for the mineral blocks on the map */
int *mineral_blocks = NULL;
pthread_mutex_t *mineral_block_mutexes = NULL;

int cc_minerals = 0; // + soldiers*50 + (scv-5{initial scv don't count})*50 == MINERAL_BLOCKS * MINERALS
pthread_mutex_t cc_minerals_mutex;

// pthread_t        scv_threads[MAX_UNITS]; /* TODO: make it dynamic memory*/
// pthread_t *scv_threads = NULL;
/* mutex for dynamic set of SCVs */
// pthread_mutex_t *scvs_mutexes = NULL;
/* variable to indicate when the dynamic memory is working*/
// int *is_scv_paused;

/* functions to be run on additional threads */
void *scv(void *id);
void *user_input();
scv_t *scvs_a = NULL;

/* helping functions for cleaner code */
void create_scv();

/* helpful functions for beginning and ending of program */
void init(int, char **);
void outit();

void get_additional_memory();

int main(int argc, char *argv[]) {
    /* init mutexes, set dynamic memory and console args */
    init(argc, argv);
    /* creating threads for initial SCVs */
    for (long scv_count = 0; scv_count < scvs; ++scv_count)
        create_thread(scvs_a[scv_count].thread, NULL, scv, (void *)&scvs_a[scv_count]);

    /* creating thread explicitly for user input  */
    pthread_t userInput;
    create_thread(&userInput, NULL, user_input, NULL);

    /* waiting for all soldiers to be completed */
    join_thread(&userInput, NULL);

    /* waiting for all minerals to be mined */
    for (int i = 0; i < scvs; ++i)
        join_thread(scvs_a[i].thread, NULL);

    /* before the end printing the state of the game */
    printf("Map minerals %d, player minerals %d, SCVs %ld, Marines %d\n",
           MINERAL_BLOCKS * MINERALS, cc_minerals, scvs, soldiers);

    /* destroy mutexes and free memory*/
    outit();

    return 0;
}

void *scv(void *arg) {
    scv_t *scv = (scv_t *)arg;
    // Step 6 - over again
    while (
        hasMinerals(MINERAL_BLOCKS,
                    MINERALS,
                    mineral_block_mutexes,
                    mineral_blocks) &&
        !*scv->signal_stop) {
        // printf("SCV %d has SIGNAL_STOP %d \n", *scv->id, *scv->signal_stop);
        for (int i = 0; i < MINERAL_BLOCKS && !*scv->signal_stop; ++i) {
            sleep(3);
            // Step 2 - check if mineral block is empty
            if (canMine(&mineral_blocks[i], MINERALS, &mineral_block_mutexes[i])) { // !0 == true
                // Step 3 - dig minerals - 0 sec
                if (mutex_trylock(&mineral_block_mutexes[i])) {
                    printf("SCV %d is mining from mineral block %d\n", *scv->id, i + 1);
                    int taken_minerals = (mineral_blocks[i] >= MINERALS - 8) ? MINERALS - mineral_blocks[i] : 8;
                    mineral_blocks[i] += taken_minerals;
                    mutex_unlock(&mineral_block_mutexes[i]);
                    // Step 4 - transporting 2 sec
                    printf("SCV %d is transporting minerals\n", *scv->id);
                    sleep(2);
                    // Step 5 - delivering 0 sec;
                    mutex_lock(&cc_minerals_mutex);
                    cc_minerals += taken_minerals;
                    mutex_unlock(&cc_minerals_mutex);
                    printf("SCV %d delivered minerals to the Command center\n", *scv->id);
                }
            }
        }
    }
    // printf("SCV %d is stopping has signal_stop %d \n", *scv->id, *scv->signal_stop);

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
                if (cc_minerals >= SOLDIER_COST)
                    create_soldier(&cc_minerals, &soldiers);
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
                if (cc_minerals >= SCV_COST)
                    create_scv();
                else {
                    printf("Not enough minerals.\n");
                    mutex_unlock(&cc_minerals_mutex);
                }
            }
            break;
        case 'q':
            break;
        }
    }
}

// TODO: get it outside of main.c
void create_scv() {
    cc_minerals -= SCV_COST;
    mutex_unlock(&cc_minerals_mutex);
    if (scvs >= SCV_CAPACITY){
        get_additional_memory();
    }
    sleep(1);

    scvs_a[scvs].id = (int *)malloc(sizeof(int));
    *scvs_a[scvs].id = (int)scvs;

    scvs_a[scvs].signal_stop = (int *)malloc(sizeof(int));
    *scvs_a[scvs].signal_stop = 0;

    scvs_a[scvs].thread = (pthread_t *)malloc(sizeof(pthread_t));
    // printf("MALLOC SCV %ld\n", scvs);
    create_thread(scvs_a[scvs].thread, NULL, scv, (void *)&scvs_a[scvs]);
    // printf("id for %ld\n", scvs);

    scvs_a[scvs].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    mutex_init(scvs_a[scvs].mutex, NULL);

    ++scvs;
    printf("SCV good to go, sir.\n");
}

void init(int argc, char *argv[]) {
    if (argc >= 2) {
        MINERAL_BLOCKS = atoi(argv[1]);
    }
    scvs_a = (scv_t *)malloc(sizeof(scv_t) * SCV_CAPACITY);
    for (int i = 0; i < scvs; i++) {
        scvs_a[i].id = (int *)malloc(sizeof(int));
        *scvs_a[i].id = i + 1;
        scvs_a[i].signal_stop = (int *)malloc(sizeof(int));
        *scvs_a[i].signal_stop = 0;
        scvs_a[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
        scvs_a[i].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        mutex_init(scvs_a[i].mutex, NULL);
    }

    mineral_blocks = (int *)realloc(mineral_blocks, sizeof(int) * MINERAL_BLOCKS);
    mineral_block_mutexes = (pthread_mutex_t *)realloc(mineral_block_mutexes, sizeof(pthread_mutex_t) * MINERAL_BLOCKS);
    memset(mineral_blocks, 0, MINERAL_BLOCKS * sizeof(int));

    for (int i = 0; i < MINERAL_BLOCKS; ++i)
        mutex_init(&mineral_block_mutexes[i], NULL);

    mutex_init(&cc_minerals_mutex, NULL);
}

void outit() {
    for (int i = 0; i < MINERAL_BLOCKS; ++i)
        mutex_destroy(&mineral_block_mutexes[i]);

    mutex_destroy(&cc_minerals_mutex);

    for (int i = 0; i < scvs; ++i) {
        mutex_destroy(scvs_a[i].mutex);
    }

    free(mineral_blocks);
    free(mineral_block_mutexes);
    for (int i = 0; i < scvs; i++) {
        free(scvs_a[i].id);
        free(scvs_a[i].mutex);
        free(scvs_a[i].thread);
        free(scvs_a[i].signal_stop);
    }
    free(scvs_a);
}

void get_additional_memory() {
    // signal every scv to stop working and then join
    // printf("GETTING ADDITIONAL MEMORY...\n");
    for (int i = 0; i < SCV_CAPACITY; i++) {
        // printf("Signalling %d SCV to stop...\n", i);
        signal_scv(&scvs_a[i]);
        // printf("Joining %d SCV...\n", i);
        join_thread(scvs_a[i].thread, NULL);
    }
    // printf("REALLOCATING SCVS_A...\n");
    // realloc all scvs
    sleep(5);
    for (int i = 0; i < SCV_CAPACITY; ++i)
        scvs_a = (scv_t *)realloc(scvs_a, (SCV_CAPACITY * 2) * sizeof(scv_t));

    // recreate threads
    for (long i = 0; i < SCV_CAPACITY; ++i)
        create_thread(scvs_a[i].thread, NULL, scv, (void *)&scvs_a[i]);

    for (int i = 0; i < SCV_CAPACITY; i++)
        signal_scv(&scvs_a[i]);

    SCV_CAPACITY *= 2;
}
