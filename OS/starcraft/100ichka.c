//------------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: StarCraft III
// FILE NAME: main.c
// FILE PURPOSE:
// Да се реализира прототип на StarCraft III
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#define MAX_PEOPLE 200

int MINERALS_PER_BLOCK = 500;
int MINERAL_BLOCKS = 2;
int MAP_MINERALS = 1000;
int PLAYER_MINERALS = 0;

long SCVs = 5;
long MARINES = 0;

pthread_t *scvs;

pthread_mutex_t blocks_mutex;
int *blocks;

pthread_mutex_t minerals;
pthread_mutex_t scv_mutex;
pthread_mutex_t marine_mutex;

//------------------------------------------------------------------------------
// FUNCTION: is_number()
// Проверява дали даден string е число
// PARAMETERS:
// Входен string
//------------------------------------------------------------------------------
int is_number(const char *string) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] < '0' || string[i] > '9') {
            return 0; // false
        }
    }

    return 1; // true
}

//------------------------------------------------------------------------------
// FUNCTION: find_first_free_block()
// Връща index на първия непразен блок.
// Ако няма такъв връща -1.
// PARAMETERS:
// няма
//------------------------------------------------------------------------------
int find_first_free_block() {
    int block_index = -1; // not found

    pthread_mutex_lock(&blocks_mutex);
    for (int i = 0; i < MINERAL_BLOCKS; i++) {
        if (blocks[i] > 0) {
            block_index = i;
            break;
        }
    }
    pthread_mutex_unlock(&blocks_mutex);

    return block_index;
}

void* scv(void* index) {
    while (1) {
        int block_index = find_first_free_block();
        int minerals_got = 0;

        if (block_index != -1) {

            if (pthread_mutex_trylock(&blocks_mutex) == 0) {
                sleep(3);
                printf("SCV %ld is mining from mineral block %d\n", (long)index, block_index+1);
                pthread_mutex_unlock(&blocks_mutex);

                pthread_mutex_lock(&blocks_mutex);
                if (blocks[block_index] >= 8) {
                    pthread_mutex_unlock(&blocks_mutex);
                    pthread_mutex_lock(&blocks_mutex);
                    minerals_got = 8;
                    blocks[block_index] -= 8;
                    pthread_mutex_unlock(&blocks_mutex);
                } else if (blocks[block_index] > 0 && blocks[block_index] < 8) {
                    pthread_mutex_unlock(&blocks_mutex);
                    pthread_mutex_lock(&blocks_mutex);
                    minerals_got = blocks[block_index];
                    blocks[block_index] = 0;
                    pthread_mutex_unlock(&blocks_mutex);
                }
                pthread_mutex_unlock(&blocks_mutex);

                printf("SCV %ld is transporting minerals\n", (long)index);
                sleep(2);

                pthread_mutex_lock(&minerals);
                printf("SCV %ld delivered minerals to the Command center\n", (long)index);

                PLAYER_MINERALS += minerals_got;
                MAP_MINERALS -= minerals_got;
                pthread_mutex_unlock(&minerals);
            }
        } else {
            break;
        }
    }

    return NULL;
}

void* in() {
    while (1) {
        char input = getchar();
        getchar();
        switch(input) {
            case 'm':
                pthread_mutex_lock(&minerals);
                if (PLAYER_MINERALS - 50 >= 0) {
                    pthread_mutex_unlock(&minerals);
                    pthread_mutex_lock(&minerals);
                    PLAYER_MINERALS -= 50;
                    pthread_mutex_unlock(&minerals);

                    sleep(1);

                    pthread_mutex_lock(&marine_mutex);
                    MARINES++;
                    pthread_mutex_unlock(&marine_mutex);

                    printf("You wanna piece of me, boy?\n");
                } else {
                    pthread_mutex_unlock(&minerals);
                    printf("Not enough minerals.\n");
                }

                break;

            case 's':
                pthread_mutex_lock(&minerals);
                if (PLAYER_MINERALS - 50 >= 0) {
                    pthread_mutex_unlock(&minerals);
                    pthread_mutex_lock(&minerals);
                    PLAYER_MINERALS -= 50;
                    pthread_mutex_unlock(&minerals);

                    sleep(4);

                    pthread_mutex_lock(&scv_mutex);
                    SCVs++;
                    pthread_mutex_unlock(&scv_mutex);

                    if (pthread_create(&scvs[SCVs], NULL, scv, (void *)(SCVs)) != 0) {
                        perror("pthread_create");
                    }

                    printf("SCV good to go, sir.\n");
                } else {
                    pthread_mutex_unlock(&minerals);
                    printf("Not enough minerals.\n");
                }

                break;
        }

        pthread_mutex_lock(&marine_mutex);
        if (MARINES == 20) {
            pthread_mutex_unlock(&marine_mutex);
            break;
        }
        pthread_mutex_unlock(&marine_mutex);

    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    if (argc == 2 && is_number(argv[1])) {
        MINERAL_BLOCKS = atoi(argv[1]);
        MAP_MINERALS = MINERAL_BLOCKS * MINERALS_PER_BLOCK;
    }

    int total_minerals = MAP_MINERALS;

    blocks = malloc(sizeof(int) * MINERAL_BLOCKS);

    for (int i = 0; i < MINERAL_BLOCKS; blocks[i++] = 500); // all blocks are full

    scvs = malloc(sizeof(pthread_t) * MAX_PEOPLE);
    pthread_t input;

    if (pthread_mutex_init(&blocks_mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        return 2;
    }

    if (pthread_mutex_init(&minerals, NULL) != 0) {
        perror("pthread_mutex_init");
        return 2;
    }
    if (pthread_mutex_init(&scv_mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        return 2;
    }
    if (pthread_mutex_init(&marine_mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        return 2;
    }

    for (long j = 0; j < SCVs; j++) {
        if (pthread_create(&scvs[j], NULL, scv, (void *)(j+1)) != 0){
            perror("pthread_create");
            return 3;
        }
    }

    if (pthread_create(&input, NULL, in, NULL) != 0){
        perror("pthread_create");
        return 3;
    }



    while (1) {
        if (MARINES == 20 && MAP_MINERALS == 0) {
            for (long j = 0; j < SCVs; j++) {
                if (pthread_join(scvs[j], NULL) != 0) {
                    perror("pthread_join");
                    return 4;
                }
            }

            if (pthread_join(input, NULL) != 0) {
                perror("pthread_join");
                return 4;
            }

            printf("Map minerals %d, player minerals %d, SCVs %ld, Marines %ld\n",
                    total_minerals, PLAYER_MINERALS, SCVs, MARINES);

            break;
        }
    }

    free(scvs);
    free(blocks);

    pthread_exit(NULL);
    return 0;
}
