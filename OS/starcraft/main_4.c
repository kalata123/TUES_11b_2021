
//----------------------------
// Name: Konstantin Donev
// class: XI b 
// Number: 17
// Problem: Make Starcraft 3(I don't know the number of it)
// File name: main.c
// File purpose: 
// Create SCVs(who are threads), which mine minerals. The whole idea is to make 20 soldiers and wait untill all SCVs mined all minerals and then kill their threads.
//----------------------------

#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


static int minerals = 0; //Here we store minerals in the base
pthread_mutex_t mineralsBase = PTHREAD_MUTEX_INITIALIZER; // This is a mutex for the minerals in base
pthread_mutex_t* blocksIndex = NULL; // this is an array of mutexes for each block of minerals
static int soldiers = 0; // Here we keep the number of soldiers
static long scv = 0; // here we keep the number of SCVs we have
static int mineralCount; // here we keep the number of mineral blocks we should have 
static int* mineralBlocks = NULL; // this as an integer array for the mineral blocks, which should be mined

//----------------------------
// Function: create_scv(void* num)
// This function is used by the scv threads and it has to simulate the work of a SCV mining minerals from mineral blocks.
void* create_scv(void* num) {
    long index = (long)num; // this is for the number of scv
    while(1){
        for (int i = 0; i < mineralCount; ++i) {
            if(mineralBlocks[i] == 0){ 
                continue; // we continue if the current block is empty
            }
            sleep(3);
            if(pthread_mutex_trylock(&blocksIndex[i]) == 0){ // we try to lock the mutex for mineral block[i]. If it's locked, the SCV continues to the next block
            	if(mineralBlocks[i] == 0){
            		pthread_mutex_unlock(&blocksIndex[i]); // we unlock the mutex because it's empty
               		continue; // we continue to the next iteration
            	}
                printf("SCV %ld is mining from mineral block %d\n", index, i+1);
                int mineralsMined = 8;
                if(mineralBlocks[i] < 8){
                    mineralsMined = mineralBlocks[i];
                }
                mineralBlocks[i] -= mineralsMined;
                pthread_mutex_unlock(&blocksIndex[i]); // we unlock the mutex because this block has already been mined by the scv 
                printf("SCV %ld is transporting minerals\n", index);
                sleep(2);
                pthread_mutex_lock(&mineralsBase); // we wait untill we can lock the mutex for the minerals in base
                minerals += mineralsMined;
                printf("SCV %ld delivered minerals to the Command Center\n", index);
                pthread_mutex_unlock(&mineralsBase); // we unlock the minerals in base, they are no longer needed
                
            }
        }
        pthread_mutex_lock(&mineralsBase); 
        if(mineralCount * 500 == minerals + (scv-5 + soldiers) * 50){ // we check if all blocks are empty
        	pthread_mutex_unlock(&mineralsBase);
        	break;
        }
        pthread_mutex_unlock(&mineralsBase);
    }
    return NULL; // this is the end of the thread
}

int main(int argc, char *argv[]) {

    if(argc == 1){
        mineralCount = 2;
    } else{
        mineralCount = atoi(argv[1]); 
    }
    mineralBlocks = (int*)malloc(mineralCount * sizeof(int));
    blocksIndex = (pthread_mutex_t*)malloc(mineralCount * sizeof(pthread_mutex_t));
    for (int i = 0; i < mineralCount; ++i) {
        mineralBlocks[i] = 500;
        pthread_mutex_init(&blocksIndex[i], NULL); // here we initialize the mutexes for each mineral block
    }
    pthread_t *scvthread = (pthread_t*)malloc(5 * sizeof(pthread_t));

    for(int i = 0; i < 5; i++){
        scv++;
        if(pthread_create(&scvthread[i], NULL, create_scv, (void *) scv) != 0){ // here we create the first five threads for SCVs
        	perror("pthread_create");
        	exit(1);
        }
    }
    while(1) {
        char ch;
        if((ch = getchar())) {
            switch (ch) {
                case 's':
                	pthread_mutex_lock(&mineralsBase); 
                    if (minerals >= 50) {
                        minerals -= 50;
                        pthread_mutex_unlock(&mineralsBase);
                        scv++;
                        scvthread = (pthread_t *) realloc(scvthread, scv * sizeof(pthread_t));
                        sleep(4);
                        printf("SCV good to go, sir.\n");
                        if(pthread_create(&scvthread[scv - 1], NULL, create_scv, (void *) scv) != 0){
                        	perror("pthread_create");
        					exit(1);
                        }
                     } else {
                     	printf("Not enough minerals.\n");
                     	pthread_mutex_unlock(&mineralsBase);
                     }
                    	break;
                case 'm':
                	pthread_mutex_lock(&mineralsBase);
                    if (minerals >= 50) {
                    	minerals -= 50;
                        soldiers++;
                        pthread_mutex_unlock(&mineralsBase);
                        sleep(1);
                        printf("You wanna piece of me, boy?\n");
                    } else {
                        printf("Not enough minerals.\n");
                        pthread_mutex_unlock(&mineralsBase);
                    }
                    break;
            }
        }
        if(soldiers >= 20){
            break;
        }
    }
    
    for(int i = 0; i < scv; ++i) {
        if(pthread_join(scvthread[i], NULL) != 0){ // we wait for all threads to finish their work, then we join and kill them
        	perror("pthread_join");
        	exit(1);
        }
    }
    
    free(scvthread);
    free(mineralBlocks);
    free(blocksIndex);
    printf("Map minerals %d, player minerals %d, SCVs %ld, Marines %d\n", mineralCount * 500, minerals, scv, soldiers);
}
