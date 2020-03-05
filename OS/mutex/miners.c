#include "pthread.h"
#include "stdio.h"
#include "unistd.h"

#define NUM_ACTIONS 20
#define GOLD_GATHER_RATE 10
#define GOLD_SELL_RATE 10

pthread_mutex_t lock;
unsigned int gold;

void * trader(void *);
void * miner(void *);

int main(int argc, char const *argv[])
{
    gold = 0;
    pthread_mutex_init(&lock, NULL);

    pthread_t miner_th;
    pthread_t trader_th;

    pthread_create(&miner_th, NULL, miner, (void*)1);
    pthread_create(&trader_th, NULL, trader, (void*)0);

    pthread_join(miner_th, NULL);
    pthread_join(trader_th, NULL);

    printf("GOLD: %ud ", gold);

    pthread_mutex_destroy(&lock);
    return 0;
}


void *miner(void *id){
    long miner_id = (long)id;
    for(int i = 0; i < NUM_ACTIONS; ++i){
        pthread_mutex_lock(&lock);
        gold += GOLD_GATHER_RATE;
        pthread_mutex_unlock(&lock);
        printf("Miner %ld is digging\n", miner_id);
        sleep(2);
    }
    return NULL;
}

void *trader(void *id){
    long trader_id = (long)id;
    for(int i = 0; i < NUM_ACTIONS; ++i){
        if(gold){
            pthread_mutex_lock(&lock);
            gold -= GOLD_SELL_RATE;
            pthread_mutex_unlock(&lock);
            printf("trader %ld is selling\n", trader_id);
        }else
        {
            printf("Trader %ld cant sell - no gold to sell\n", trader_id);
        }
        sleep(2);
    }

    return NULL;
}