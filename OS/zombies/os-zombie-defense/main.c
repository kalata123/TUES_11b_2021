#include "ui.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *create_solder(void *);
void *create_miner();
void *create_zombies();

int zombies = 1, soldiers = 0, lives = 100, gold = 100;

pthread_mutex_t mutex;

int main() {
	init();
	print_gold(gold);
	print_soldiers(soldiers);
	print_zombies(5, zombies);
	print_health(lives);

	pthread_mutex_init(&mutex, NULL);

	pthread_t zombie_thread;
	pthread_create(&zombie_thread, NULL, create_zombies, NULL);
	while(1) {
		int ch;
		ch = lives ? get_input() : 'q';
		switch(ch) {
			case 'q':
				game_end(zombies);
				break;
			case 'm':;
				pthread_t miner_thread;
				printf("%c\n",ch);
				// if (gold >= 100){
				// 	pthread_mutex_lock(&mutex);
				// 	gold -= 100;
				// 	print_gold(gold);
				// 	pthread_mutex_unlock(&mutex);
				// 	pthread_create(&miner_thread, NULL, create_miner, NULL);
				// }
				break;
			case 'x':;
				pthread_t x10_soldier_thread;
				if (gold >= 100){
					pthread_create(&x10_soldier_thread, NULL, create_solder, (void *)10);
					print_msg("asd");
				}
				break;
			case 's':;
				pthread_t soldier_thread;
				print_msg("dsa");
				if (gold >= 10){
				pthread_create(&soldier_thread, NULL, create_solder, (void *)1);
				}
				break;
		}
	}

	pthread_mutex_destroy(&mutex);
	return 0;
}

void *create_solder(void * num){
	long soldiers_count = (long) num;
	if (soldiers_count == 1){
		pthread_mutex_lock(&mutex);
		soldiers += 1;
		gold -= 10;
		print_gold(gold);
		print_soldiers(soldiers);
		pthread_mutex_unlock(&mutex);
	}else
	{
		pthread_mutex_lock(&mutex);
		soldiers += 10;
		gold -= 100;
		print_gold(gold);
		print_soldiers(soldiers);
		pthread_mutex_unlock(&mutex);
	}
	
}

void *create_miner(){
	while (1)
	{
		pthread_mutex_lock(&mutex);
		printf("miner digging\n");
		gold += 10;
		print_gold(gold);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
}

void *create_zombies(){
	while (1)
	{
		pthread_mutex_lock(&mutex);
		for (int i = 5; i >= 0; --i){
			print_zombies(i, zombies);
			sleep(1);
		}

		if (zombies > soldiers){
			lives -= (zombies - soldiers);
			print_fail("Zombie attack succeded ;(!");
			print_health(lives);
			if (lives <= 0) game_end(zombies);
		}else {
			print_succ("Zombie attack deflected!:)");
		}

		zombies *= 2;
		pthread_mutex_unlock(&mutex);
	}
}