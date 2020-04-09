#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/*
Some global variables that DO NOT change during the runtime
*/
#define MAX_UNITS 200 // scvs + soldiers <= 200
#define MINERALS  500 // minerals in each mineral block
#define SOLDIERS   20 // needed soldiers to finish the game

/*
Some global variables that DO change during the runtime
*/
int MINERAL_BLOCKS  = 2, // total mineral blocs
    soldiers        = 0, // need 20 to win
    cc_minerals     = 0; // + soldiers*50 + (scv-5{initial scv don't count})*50 == MINERAL_BLOCKS * MINERALS
long scvs = 5; // workers that dig minerals

int *mineral_blocks = NULL;


pthread_t        scv_threads[MAX_UNITS];
pthread_mutex_t* mineral_block_mutexes = NULL; // must be dynamic for console args to work
pthread_mutex_t  cc_minerals_mutex;

// functions for threads
void *scv(void *id);
void *user_input();

// helping functions
void create_soldier();
void create_scv();
int  hasMinerals();
int  canMine(int *, pthread_mutex_t *);
void init();
void outit();

int  mutex_trylock(pthread_mutex_t *);
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
        MINERAL_BLOCKS * MINERALS, cc_minerals, scvs, soldiers);
    outit();
    return 0;
}

void *scv(void *id){        
    // Step 6 - over again
    while (hasMinerals()){
        for (int i = 0; i < MINERAL_BLOCKS; ++i){
            sleep(3);
            // Step 2 - check if mineral block is empty
            if (canMine(&mineral_blocks[i], &mineral_block_mutexes[i])){ // !0 == true
                // Step 3 - dig minerals - 0 sec
                if (mutex_trylock(&mineral_block_mutexes[i])){
                    printf("SCV %ld is mining from mineral block %d\n", (long)id, i + 1);
                    int taken_minerals = (mineral_blocks[i] >= MINERALS - 8) ? MINERALS - mineral_blocks[i] : 8; // should be out of sycle - used in another place, too
                    mineral_blocks[i] += taken_minerals;
                    mutex_unlock(&mineral_block_mutexes[i]);
                    // Step 4 - transporting 2 sec
                    printf("SCV %ld is transporting minerals\n", (long)id);
                    sleep(2);
                    // Step 5 - delivering 0 sec
                    mutex_lock(&cc_minerals_mutex);
                    cc_minerals += taken_minerals;
                    mutex_unlock(&cc_minerals_mutex);
                    printf("SCV %ld delivered minerals to the Command center\n", (long)id);
                }
            }
        }
    }
    return NULL;
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
                    mutex_lock(&cc_minerals_mutex);
                    cc_minerals >= 50 ? create_soldier() : printf("Not enough minerals.\n");
                    mutex_unlock(&cc_minerals_mutex);
                    if (soldiers >= SOLDIERS) {
                        return NULL;
                    }  
                }
                break;
            case 's':
                if (scvs + soldiers < MAX_UNITS) {
                    mutex_lock(&cc_minerals_mutex);
                    cc_minerals >= 50 ? create_scv() : printf("Not enough minerals.\n");
                    mutex_unlock(&cc_minerals_mutex);
                }
                break;
            case 'q':
                break;
        }
    }
}

void create_soldier(){
    cc_minerals -= 50;
    sleep(1);
    soldiers += 1;
    printf("You wanna piece of me, boy?\n");
}

void create_scv(){
    cc_minerals -= 50;
    sleep(4);
    create_thread(&scv_threads[scvs], NULL, scv, (void *)(++scvs));
    printf("SCV good to go, sir.\n");
}

int hasMinerals(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
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

int canMine(int* mineral, pthread_mutex_t* mutex){
    mutex_lock(mutex);
    if (*mineral < MINERALS){
        mutex_unlock(mutex);
        return 1;
    }
    mutex_unlock(mutex);
    return 0;
}

void init(){
    for (int i = 0; i < MINERAL_BLOCKS; ++i){
        if (pthread_mutex_init(&mineral_block_mutexes[i], NULL) != 0){
            perror("Initializing mineral mutexes");
            pthread_exit(NULL);
            exit(0);
        }
    }
    if (pthread_mutex_init(&cc_minerals_mutex, NULL) != 0){
        perror("Initializing Command center minerals mutex");
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
    if (pthread_mutex_destroy(&cc_minerals_mutex) != 0){
        perror("Destroying Command center minerals mutex");
        pthread_exit(NULL);
        exit(0);
    }
    free(mineral_blocks);
    free(mineral_block_mutexes);
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