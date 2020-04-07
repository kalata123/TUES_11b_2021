#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_UNITS 200  // scvs + soldiers <= 200
#define MINERALS 500
#define SOLDIERS 20

int MINERAL_BLOCKS = 2, // total mineral blocs
    soldiers = 0, // need 20 to wi
    minerals_in_stock = 0; // + soldiers*50 + (scv-5{initial scv don't count})*50 == MINERAL_BLOCKS * MINERALS
long scvs = 5; // workers that dig minerals

int *mineral_blocks = NULL;


pthread_t scv_threads[MAX_UNITS];
pthread_mutex_t *mineral_block_mutexes = NULL; // must be dynamic for console args to work
pthread_mutex_t command_center_minerals_mutex,
                command_center_soldiers_mutex;

// void command_center();
void *scv(void *shof);
void *check_win_lose();
void *user_input();
void create_soldier();
// int check_enough_minerals(int);

void init();
void outit();
int hasMinerals();

int main(int argc, char *argv[]) {
    if (argc >= 2){
        MINERAL_BLOCKS = atoi(argv[1]);
    }
    mineral_blocks = (int *) realloc(mineral_blocks, sizeof(int) * MINERAL_BLOCKS);
    mineral_block_mutexes = (pthread_mutex_t *) realloc(mineral_block_mutexes, sizeof(pthread_mutex_t) * MINERAL_BLOCKS);
    memset(mineral_blocks, 0, MINERAL_BLOCKS*sizeof(int));
    init();
    long scv_count = 0;

    // start scv's
    for (; scv_count < 5; ++scv_count){
        if (pthread_create(&scv_threads[scv_count], NULL, scv, (void *)(scv_count + 1))){
            perror("Creating initial SCVs");
            pthread_exit(NULL);
            exit(0);
        }
    }

    pthread_t userInput;
    if (pthread_create(&userInput, NULL, user_input, NULL)){
        perror("create user input thread in main");
        pthread_exit(NULL);
        exit(0);
    }

    if (pthread_join(userInput, NULL)){
        perror("Joining error");
        pthread_exit(NULL);
        exit(0);
    }

    for (int i = 0; i < scvs; ++i) {
        if (pthread_join(scv_threads[i], NULL)){
            perror("Joining error");
            pthread_exit(NULL);
            exit(0);
        }
    }

    printf("Map minerals %d, player minerals %d, SCVs %ld, Marines %d\n",
        MINERAL_BLOCKS * MINERALS, minerals_in_stock, scvs, soldiers);
    outit();
    pthread_exit(NULL);
    return 0;
}

void create_soldier(){
    if (pthread_mutex_lock(&command_center_minerals_mutex)){
        perror("minerals mutex in create soldier");
    }
    minerals_in_stock -= 50;
    if (pthread_mutex_unlock(&command_center_minerals_mutex) != 0){
        perror("Pthread unlock mineral blocks in scv");
    }
    sleep(1);
    soldiers += 1;
    printf("You wanna piece of me, boy?\n");
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
        if (pthread_mutex_destroy(&mineral_block_mutexes[i]) != 0){
            perror("Destroying mineral minerals mutexes");
        }
    }
    if (pthread_mutex_destroy(&command_center_minerals_mutex) != 0){
        perror("Destroying Command center minerals mutex");
    }
    if (pthread_mutex_destroy(&command_center_soldiers_mutex) != 0){
        perror("Destroying Command center soldiers mutex");
    }
    free(mineral_blocks);
    free(mineral_block_mutexes);
}


int hasMinerals(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
        if (mineral_blocks[i] < MINERALS) {
            return 1;
        }
    }
    return 0;
}

void *scv(void *id){        
    // Step 6 - over again
    while (1){
        for (int i = 0; i < MINERAL_BLOCKS; ++i){
            sleep(3);
            // Step 2 - check if mineral block is empty
            if (mineral_blocks[i] < MINERALS){ // !0 == true
                // Step 3 - dig minerals - 0 sec 
                if (!pthread_mutex_trylock(&mineral_block_mutexes[i])){
                    printf("SCV %ld is mining from mineral block %d\n", (long)id, i + 1);
                    int taken_minerals = 0; // should be out of sycle - used in another place, too
                    for (; taken_minerals < 8 || mineral_blocks[i] < MINERALS; ++mineral_blocks[i], ++taken_minerals);
                    // FOR: increments the used mineral_blocks and increments the taken minerals by the scv
                    if (pthread_mutex_unlock(&mineral_block_mutexes[i])){
                        perror("Unlock mineral block failed");
                    }
                    // Step 4 - transporting 2 sec
                    printf("SCV %ld is transporting minerals\n", (long)id);
                    sleep(2);
                    // Step 5 - delivering 0 sec
                    pthread_mutex_lock(&command_center_minerals_mutex);
                    minerals_in_stock += taken_minerals;
                    pthread_mutex_unlock(&command_center_minerals_mutex);
                    printf("SCV %ld delivered minerals to the Command center\n", (long)id);
                }
            }
        }

        if (!hasMinerals()){ // all mineral blocks are empty
            return NULL; // the scv is no longer needed.
        }
    }
}

void *user_input(){
    char ch;
    while (1)
    {
        scanf("%c",&ch);
        switch (ch){
            case 'm':
                if (scvs + soldiers < MAX_UNITS) {
                    minerals_in_stock >= 50 ? create_soldier() : printf("Not enough minerals.\n");
                    if (soldiers >= SOLDIERS) {
                        return NULL;
                    }  
                }
                break;
            case 's':
                if (scvs + soldiers < MAX_UNITS) {
                    if (minerals_in_stock >= 50) {
                        if (pthread_mutex_lock(&command_center_minerals_mutex)){
                            perror("minerals mutex in create soldier");

                        }
                        minerals_in_stock -= 50;
                        if (pthread_mutex_unlock(&command_center_minerals_mutex) != 0){
                            perror("Pthread unlock mineral blocks in input for scv");
                        }
                        sleep(4);
                        if (pthread_create(&scv_threads[scvs], NULL, scv, (void *)(++scvs))){
                            perror("Creating additional SCVs");
                        }
                        printf("SCV good to go, sir.\n");
                    } else {
                        printf("Not enough minerals.\n");
                    }
                } else {
                    printf("You are trying to create more than allowed units\n");
                }
                break;
            case 'q':
                break;
        }
    }
}

