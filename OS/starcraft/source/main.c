//--------------------------------------------
// NAME: Kaloyan Angelov
// CLASS: Xib
// NUMBER: 15
// PROBLEM: #3
// FILE NAME: main.c
// FILE PURPOSE:
// main functionality for the starcraft3 game
//---------------------------------------------
/* TODO: refactor using __sync_add_and_fetch type funcs (atomic) */
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
#define SOLDIERS 20   // needed soldiers to finish the game
#define SCV_COST 50
#define SOLDIER_COST 50

/* Some global variables that DO CHANGE during the runtime s*/
int MINERAL_BLOCKS = 2, // total mineral blocks
    soldiers = 0;       // total soldiers

/* SCV variables. */
long scvs = 5;          // SCVs count
long SCV_CAPACITY = 10; // SCVs capacity

/* variables for the mineral blocks on the map */
int *mineral_blocks = NULL;                    // Mineral blocks on the map
pthread_mutex_t *mineral_block_mutexes = NULL; // Mineral blocks mutexes

int cc_minerals = 0;               // Total minerals
pthread_mutex_t cc_minerals_mutex; // Mutex for total minerals

/* functions to be run on additional threads */
void *scv(void *arg); // SCV routine function
void *user_input();   // User input function

/* Pointer for all SCVs*/
scv_t *scvs_a = NULL; // All<(long)scvs> SCVs

/* helping functions for cleaner code */
void create_scv();            // Creates additional scv
void init(int, char **);      // initializes core variables
void outit();                 // destroyes and frees everything
void get_additional_memory(); // Doubles <(scv_t *)scvs_a> and multiples <(long)SCV_CAPACITY>

/* Main */
int main(int argc, char *argv[]) {
    //--------------------------------------------
    // FUNCTION: main
    // program begins and game starts
    // PARAMETERS:
    // console arguments
    //----------------------------------------------

    /* init mutexes, set dynamic memory and console args */
    init(argc, argv);

    /* creating threads for initial SCVs */
    for (long scv_count = 0; scv_count < scvs; ++scv_count)
        create_thread(scvs_a[scv_count].thread, NULL, scv, (void *)&scvs_a[scv_count]);

    /* creating thread explicitly for user input */
    // Might prove useless
    pthread_t userInput;
    create_thread(&userInput, NULL, user_input, NULL);

    /* waiting for all soldiers to be completed */
    // Could imrpove
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
    //--------------------------------------------
    // FUNCTION: scv
    // SCV routine function
    // PARAMETERS:
    // void *arg - type is scv_t and arg is curr SCV
    //----------------------------------------------
    scv_t *scv = (scv_t *)arg; // Cast to scv_t
    // Step 6 - over again
    while (
        hasMinerals(MINERAL_BLOCKS,
                    MINERALS,
                    mineral_block_mutexes,
                    mineral_blocks) &&
        !*scv->signal_stop) {

        for (int i = 0; i < MINERAL_BLOCKS && !*scv->signal_stop; ++i) {
            sleep(3);
            // Step 2 - check if mineral block is empty and move there
            if (canMine(&mineral_blocks[i], MINERALS, &mineral_block_mutexes[i])) { // !0 == true
                // Step 3 - dig minerals - 0 sec
                if (mutex_trylock(&mineral_block_mutexes[i])) {
                    // print MSG
                    printf("SCV %d is mining from mineral block %d\n", *scv->id, i + 1);

                    // dig minerals
                    int taken_minerals = (mineral_blocks[i] >= MINERALS - 8) ? MINERALS - mineral_blocks[i] : 8;
                    mineral_blocks[i] += taken_minerals;

                    // unlock from trylock
                    mutex_unlock(&mineral_block_mutexes[i]);

                    // Step 4 - transporting 2 sec - print MSG
                    printf("SCV %d is transporting minerals\n", *scv->id);
                    sleep(2);

                    // Step 5 - delivering 0 sec;
                    // lock total minerals
                    mutex_lock(&cc_minerals_mutex);

                    // add to total minerals
                    cc_minerals += taken_minerals;

                    // unlock total minerals
                    mutex_unlock(&cc_minerals_mutex);
                    printf("SCV %d delivered minerals to the Command center\n", *scv->id);
                }
            }
        }
    }
    return NULL;
}

void *user_input() {
    //--------------------------------------------
    // FUNCTION: user_input
    // handling user input
    // PARAMETERS: None
    //----------------------------------------------
    char ch;
    while (1) {

        // get user input
        int retcode;
        if ((retcode = scanf("%c", &ch)) == EOF) {
            printf("Mutex lock %s\n", strerror(retcode));
            pthread_exit(NULL);
            exit(0);
        }

        switch (ch) {
        case 'm': // case Marines

            // check if valid request
            if (scvs + soldiers < MAX_UNITS) {

                // lock total minerals
                mutex_lock(&cc_minerals_mutex);

                // check if enough minerals
                if (cc_minerals >= SOLDIER_COST)
                    // create soldier
                    create_soldier(&cc_minerals, &soldiers);
                else // not enough minerals
                    printf("Not enough minerals.\n");

                // unlock total minerals
                mutex_unlock(&cc_minerals_mutex);

                // check if soldiers more than 20
                if (soldiers >= SOLDIERS) {
                    return NULL; // stop thread
                }
            }
            break;
        case 's': // case scvs

            // check if valid request
            if (scvs + soldiers < MAX_UNITS) {

                // lock total minerals
                mutex_lock(&cc_minerals_mutex);

                // check if enough minerals
                if (cc_minerals >= SCV_COST)
                    // create scv AND unlock total minerals
                    create_scv();
                else { // not enough minerals
                    printf("Not enough minerals.\n");

                    // unlock total minerals
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
    //--------------------------------------------
    // FUNCTION: create_scv
    // creates new SCV - with dynamic memory
    // PARAMETERS: None yet
    //----------------------------------------------

    // substract from total minerals
    cc_minerals -= SCV_COST;

    // unlock total minerals
    mutex_unlock(&cc_minerals_mutex);

    // check if enough capacity
    if (scvs >= SCV_CAPACITY)
        // realloc additional memory
        get_additional_memory();

    // malloc new memory and set initial values
    scvs_a[scvs].id = (int *)malloc(sizeof(int));
    *scvs_a[scvs].id = (int)scvs;

    scvs_a[scvs].signal_stop = (int *)malloc(sizeof(int));
    *scvs_a[scvs].signal_stop = 0;

    scvs_a[scvs].thread = (pthread_t *)malloc(sizeof(pthread_t));

    scvs_a[scvs].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    mutex_init(scvs_a[scvs].mutex, NULL);

    // sleep while scv is training
    sleep(1);

    // create new thread for SCV
    create_thread(scvs_a[scvs].thread, NULL, scv, (void *)&scvs_a[scvs]);

    // increment total scvs
    ++scvs;

    printf("SCV good to go, sir.\n");
}

void init(int argc, char *argv[]) {
    //--------------------------------------------
    // FUNCTION: init
    // initializes core variables
    // PARAMETERS:
    // console arguments - used to set initial values
    //----------------------------------------------

    // check if any console arguments
    if (argc >= 2)
        // set total mineral blocks to console argument
        MINERAL_BLOCKS = atoi(argv[1]);

    // malloc enough memory for all inital scv and same amount more
    scvs_a = (scv_t *)malloc(sizeof(scv_t) * SCV_CAPACITY);

    // for every initial scv
    for (int i = 0; i < scvs; i++) {
        // malloc new memory and set initial values
        scvs_a[i].id = (int *)malloc(sizeof(int));
        *scvs_a[i].id = i + 1;

        scvs_a[i].signal_stop = (int *)malloc(sizeof(int));
        *scvs_a[i].signal_stop = 0;

        scvs_a[i].thread = (pthread_t *)malloc(sizeof(pthread_t));

        scvs_a[i].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));

        // initialize SCV mutex
        mutex_init(scvs_a[i].mutex, NULL);
    }

    // malloc every mineral block and set its value to 0
    mineral_blocks = (int *)realloc(mineral_blocks, sizeof(int) * MINERAL_BLOCKS);
    memset(mineral_blocks, 0, MINERAL_BLOCKS * sizeof(int));

    // malloc mutexes for every mineral block
    mineral_block_mutexes = (pthread_mutex_t *)realloc(mineral_block_mutexes, sizeof(pthread_mutex_t) * MINERAL_BLOCKS);

    // for every mineral block
    for (int i = 0; i < MINERAL_BLOCKS; ++i)

        // initialize mutex
        mutex_init(&mineral_block_mutexes[i], NULL);

    // initialize mutex for total minerals
    mutex_init(&cc_minerals_mutex, NULL);

    return;
}

void outit() {
    //--------------------------------------------
    // FUNCTION: outit
    // destroyes and frees everything
    // PARAMETERS: None
    //----------------------------------------------

    // for every mineral block
    for (int i = 0; i < MINERAL_BLOCKS; ++i)
        // destroy mutex
        mutex_destroy(&mineral_block_mutexes[i]);

    // destroy total minerals mutex
    mutex_destroy(&cc_minerals_mutex);

    // for every SCV
    for (int i = 0; i < scvs; ++i)
        //destroy mutex
        mutex_destroy(scvs_a[i].mutex);

    // free memory for mineral blocks
    free(mineral_blocks);

    // free memory for mineral block mutexes
    free(mineral_block_mutexes);

    // for every SCV
    for (int i = 0; i < scvs; i++) {
        // free every pointer
        free(scvs_a[i].id);
        free(scvs_a[i].mutex);
        free(scvs_a[i].thread);
        free(scvs_a[i].signal_stop);
    }

    // free all SCVs
    free(scvs_a);
}

void get_additional_memory() {
    //--------------------------------------------
    // FUNCTION: get_additional_memory
    // reallocs additional memory for SCVs
    // PARAMETERS: NONE
    //----------------------------------------------

    // signal every scv to stop working and then join
    for (int i = 0; i < scvs; i++) {
        signal_scv(&scvs_a[i]);
        join_thread(scvs_a[i].thread, NULL);
    }

    // realloc all scvs
    scvs_a = (scv_t *)realloc(scvs_a, (SCV_CAPACITY * 2) * sizeof(scv_t));

    // recreate threas AND signal every SCV
    for (long i = 0; i < scvs; ++i) {
        create_thread(scvs_a[i].thread, NULL, scv, (void *)&scvs_a[i]);
        signal_scv(&scvs_a[i]);
    }

    // multiply total capacity
    SCV_CAPACITY *= 2;
}
