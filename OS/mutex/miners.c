#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int gold = 0;

void * trader(void *);
void * miner(void *);

int main(int argc, char const *argv[])
{
    long miners = 1, traders = 1;
    if (argc > 2){
        miners = atoi(argv[1]), traders = atoi(argv[2]);
    }
    pthread_t miner_threads[miners], trader_threads[traders];
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < miners; i++){
        if (pthread_create(&miner_threads[i], NULL, miner, (void*)i) == -1){
            perror("pthread_create miners");
        }
    }
    for (long i = 0; i < traders; ++i){
        if (pthread_create(&trader_threads[i], NULL, trader, (void*)i) == -1){
            perror("pthread_create traders");
        }
    }

    for (long i = 0; i < miners; i++){
        if (pthread_join(miner_threads[i], NULL) == -1) {
            perror("pthread_join miners");
        }
    }
    for (long i = 0; i < traders; ++i){
        if (pthread_join(trader_threads[i], NULL) == -1){
            perror("pthread_join traders");
        }
    }
    pthread_mutex_destroy(&mutex);

    printf("Gold: %d\n", gold);
    return 0;
}


void *miner(void *id){
    long miner_id = (long)id + 1;
    for(int i = 0; i < 20; ++i){
        pthread_mutex_lock(&mutex);
        gold += 10;
        printf("Miner %ld gathered 10 gold\n", miner_id);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

void *trader(void *id){
    long trader_id = (long)id + 1;
    for(int i = 0; i < 20; ++i){
        pthread_mutex_lock(&mutex);
        if(gold){
            gold -= 10;
            printf("Trader %ld sold 10 gold\n", trader_id);
        }else
        {
            printf("The warehouse is empty, cannot sell!\n");
        }
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}