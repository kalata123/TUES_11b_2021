#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_UNITS 200  // scvs + soldiers <= 200
#define MINERALS 500 // minerals in each mineral block
#define SOLDIERS 20 // needed soldiers to finish the game
// #define MINERALS 50 // testing defines
// #define SOLDIERS 2 // testing defines

int MINERAL_BLOCKS = 2, // total mineral blocs
    soldiers = 0, // need 20 to win
    minerals_in_stock = 0; // + soldiers*50 + (scv-5{initial scv don't count})*50 == MINERAL_BLOCKS * MINERALS
long scvs = 5; // workers that dig minerals

int *mineral_blocks = NULL;


pthread_t scv_threads[MAX_UNITS];
pthread_mutex_t *mineral_block_mutexes = NULL; // must be dynamic for console args to work
pthread_mutex_t command_center_minerals_mutex,
                command_center_soldiers_mutex;

// void command_center();
void *scv(void *id);
int hasMinerals();
void *user_input();
void create_soldier();
void create_scv();
// int check_enough_minerals(int);

void init();
void outit();

int mutex_trylock(pthread_mutex_t *);
void mutex_lock(pthread_mutex_t *);
void mutex_unlock(pthread_mutex_t *);
void join_thread(pthread_t *, void *);
void create_thread(pthread_t * thread,
                const pthread_attr_t *thread_attr,
                void *(*func) (void *),
                void *func_attr);

int main(int argc, char *argv[]) {
    if (argc >= 2){
        MINERAL_BLOCKS = atoi(argv[1]);
    }
    mineral_blocks = (int *) realloc(mineral_blocks, sizeof(int) * MINERAL_BLOCKS);
    mineral_block_mutexes = (pthread_mutex_t *) realloc(mineral_block_mutexes, sizeof(pthread_mutex_t) * MINERAL_BLOCKS);
    memset(mineral_blocks, 0, MINERAL_BLOCKS*sizeof(int));
    init();

    // start scv's
    for (long scv_count = 0; scv_count < 5; ++scv_count){
        create_thread(&scv_threads[scv_count], NULL, scv, (void *)(scv_count + 1));
    }

    pthread_t userInput;
    create_thread(&userInput, NULL, user_input, NULL);

    join_thread(&userInput, NULL);
    for (int i = 0; i < scvs; ++i) {
        join_thread(&scv_threads[i], NULL);
    }

    printf("Map minerals %d, player minerals %d, SCVs %ld, Marines %d\n",
        MINERAL_BLOCKS * MINERALS, minerals_in_stock, scvs, soldiers);
    outit();
    // pthread_exit(NULL);
    return 0;
}

void create_soldier(){
    mutex_lock(&command_center_minerals_mutex);
    minerals_in_stock -= 50;
    mutex_unlock(&command_center_minerals_mutex);
    sleep(1);
    soldiers += 1;
    printf("You wanna piece of me, boy?\n");
}

void init(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
        if (pthread_mutex_init(&mineral_block_mutexes[i], NULL) != 0){
            perror("Initializing mineral mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }
    if (pthread_mutex_init(&command_center_minerals_mutex, NULL) != 0){
        perror("Initializing Command center minerals mutex");
        pthread_exit(NULL);
        exit(0);
    }
    if (pthread_mutex_init(&command_center_soldiers_mutex, NULL) != 0){
        perror("Initializing Command center soldiers mutex");
        pthread_exit(NULL);
        exit(0);
    }
}

void outit(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
        if (pthread_mutex_destroy(&mineral_block_mutexes[i]) != 0){
            perror("Destroying mineral minerals mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }
    if (pthread_mutex_destroy(&command_center_minerals_mutex) != 0){
        perror("Destroying Command center minerals mutex");
        pthread_exit(NULL);
        exit(0);
    }
    if (pthread_mutex_destroy(&command_center_soldiers_mutex) != 0){
        perror("Destroying Command center soldiers mutex");
        pthread_exit(NULL);
        exit(0);
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
                if (mutex_trylock(&mineral_block_mutexes[i])){
                    printf("SCV %ld is mining from mineral block %d\n", (long)id, i + 1);
                    int taken_minerals = 8; // should be out of sycle - used in another place, too
                    if (mineral_blocks[i] >= MINERALS - 8) {
                        taken_minerals = MINERALS - mineral_blocks[i];
                        mineral_blocks[i] = MINERALS;
                    } else {
                        mineral_blocks[i] += taken_minerals;
                    }
                    // for (; taken_minerals < 8 || mineral_blocks[i] >= MINERALS; ++mineral_blocks[i], ++taken_minerals);
                    // FOR: increments the used mineral_blocks and increments the taken minerals by the scv
                    mutex_unlock(&mineral_block_mutexes[i]);
                    // Step 4 - transporting 2 sec
                    printf("SCV %ld is transporting minerals\n", (long)id);
                    sleep(2);
                    // Step 5 - delivering 0 sec
                    mutex_lock(&command_center_minerals_mutex);
                    minerals_in_stock += taken_minerals;
                    mutex_unlock(&command_center_minerals_mutex);
                    printf("SCV %ld delivered minerals to the Command center\n", (long)id);
                    // printf("SCV %ld delivered minerals to the Command center TOTAL: %d\n", (long)id, minerals_in_stock);
                    // for (int i = 0; i < MINERAL_BLOCKS; ++i) {
                    //     printf("Mineral Block %d has %d minerals\n", i + 1, mineral_blocks[i]);
                    // }
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
        if (scanf("%c",&ch) == EOF) {
            perror("Scanf error");
            pthread_exit(NULL);
            exit(0);
        }
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
                    minerals_in_stock >= 50 ? create_scv() : printf("Not enough minerals.\n");
                }
                break;
            case 'q':
                break;
        }
    }
}

void create_scv(){
    mutex_lock(&command_center_minerals_mutex);
    minerals_in_stock -= 50;
    mutex_unlock(&command_center_minerals_mutex);
    sleep(4);
    create_thread(&scv_threads[scvs], NULL, scv, (void *)(++scvs));
    printf("SCV good to go, sir.\n");
}

int mutex_trylock(pthread_mutex_t *mutex){
    if (pthread_mutex_trylock(mutex)){
        return 0;
    } else {
        return 1;
    }
}

void mutex_lock(pthread_mutex_t *mutex){
    if (pthread_mutex_lock(mutex)){
        perror("Mutex lock");
        pthread_exit(NULL);
        exit(0);
    }
}

void mutex_unlock(pthread_mutex_t *mutex){
    if (pthread_mutex_unlock(mutex)){
        perror("Mutex unlock");
        pthread_exit(NULL);
        exit(0);
    }
}

void join_thread(pthread_t *thread, void *ret){
    if (pthread_join(*thread, ret)){
        perror("Joining error");
        pthread_exit(NULL);
        exit(0);
    }
}

void create_thread(pthread_t * thread, const pthread_attr_t *thread_attr, void *(*func) (void *), void *func_attr){
    if (pthread_create(thread, thread_attr, func, func_attr)){
        perror("Create thread");
        pthread_exit(NULL);
        exit(0);
    }
}