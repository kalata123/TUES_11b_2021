#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "curses.h"
#include <unistd.h>

#define MINERAL_BLOCKS 2 
#define MAX_UNITS 200  // scvs + soldiers <= 200

int scvs = 5; // workers that dig minerals
int soldiers = 0; // need 20 to win
int minerals_in_stock = 0; // + soldiers*50 + (scv-5{initial scv don't count})*50 == MINERAL_BLOCKS * 500

int mineral_blocks[MINERAL_BLOCKS][500] = {0};
pthread_mutex_t mineral_block_mutexes[2], command_center_minerals_mutex, command_center_soldiers_mutex;

// void command_center();
void *scv(void *shof);

void init();
void outit();

int main(int argc, char const *argv[]) {
    init();
    // check cmd line for mineral blocks

    while (1)
    {
        int ch = getch();
        switch (ch){
            case 'm':
                // create soldier
                break;
            
            case 's':
                // create scv
                break;
            default:
                break;
            }

    }
    


    outit();
    return 0;
}

void command_center(){
    
}

void *scv(void *id){
    int empty_mineral_blocks[MINERAL_BLOCKS] = {0}; // if any block is 1 - it is empty
    int checker = 0; // checks if all mineral blocks are empty;
    // Step 6
    while (1){
        // Step 1
        for (int i = 0; i < MINERAL_BLOCKS; ++i){
            // Step 2
            if (!empty_mineral_blocks[i]){ // !0 == true
                checker = 0; // mineral block is not empty
                sleep(3); // part of Step 1
                // Step 3
                printf("SCV %ld is mining from mineral block %d\n", (long)id, i);
                if (!pthread_mutex_trylock(&mineral_block_mutexes[i])){
                    int taken_minerals = 0, k = 0;
                    for (; taken_minerals < 8 || k >= 500; ++k){
                        // taken_minerals is taken minerals 
                        // k is current mineral from the mineral block
                        if (mineral_blocks[i][k] == 0){
                            mineral_blocks[i][k] = 1;
                            ++taken_minerals;
                        }
                    }
                    if (pthread_mutex_unlock(&mineral_block_mutexes[i])){
                        perror("Unlock mineral block failed");
                    }
                    if (k >= 500){ // mineral block is empty
                        empty_mineral_blocks[i] = 1;
                    }
                    // Step 4
                    printf("SCV %ld is transporting minerals\n", (long)id);
                    sleep(2);
                    // Step 5
                    pthread_mutex_lock(&command_center_minerals_mutex);
                    minerals_in_stock += taken_minerals;
                    pthread_mutex_unlock(&command_center_minerals_mutex);
                    printf("SCV %ld delivered minerals to the Command center");
                } else{
                    continue; // edns the while true and continues to the other mineral blocks
                }
            } else{
                checker = 1; // mineral block is empty
            }
        }

        if (checker){ // all mineral blocks are empty
            return NULL; // the scv is no longer needed.
        }
    }
}


void init(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
        if (pthread_mutex_init(&mineral_block_mutexes[i], NULL) != 0){
            perror("Initializing mineral mutexes");
        }
    }
    if (pthread_mutex_init(&command_center_minerals_mutex, NULL) != 0){
        perror("Initializing Command center minerals mutex");
    }
    if (pthread_mutex_init(&command_center_soldiers_mutex, NULL) != 0){
        perror("Initializing Command center soldiers mutex");
    }
}

void outit(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
        if (pthread_mutex_destroy(&mineral_block_mutexes) != 0){
            perror("Destroying mineral minerals mutexes");
        }
    }
    if (pthread_mutex_destroy(&command_center_minerals_mutex) != 0){
        perror("Destroying Command center minerals mutex");
    }
    if (pthread_mutex_destroy(&command_center_soldiers_mutex) != 0){
        perror("Destroying Command center soldiers mutex");
    }
}