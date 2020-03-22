#include "ui.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *create_solder(void *);
void *create_miner();
void *create_zombies();

int ZOMBIES = 1, SOLDIERS = 0, LIVES = 100, GOLD = 100;

pthread_mutex_t mutex;

int main() {
	init();
	print_gold(GOLD);
	print_soldiers(SOLDIERS);
	print_health(LIVES);

	pthread_mutex_init(&mutex, NULL);

	pthread_t zombie_thread;
	pthread_create(&zombie_thread, NULL, create_zombies, NULL);

	while(1) {
		int ch = get_input();
		switch(ch) {
			case 'q':
				game_end(ZOMBIES);
				break;
			case 'm':;
				pthread_t miner_thread;
				pthread_create(&miner_thread, NULL, create_miner, NULL);
				break;
			case 'x':;
				pthread_t x10_soldier_thread;
				pthread_create(&x10_soldier_thread, NULL, create_solder, (void *)10);
				break;
			case 's':;
				pthread_t soldier_thread;
				pthread_create(&soldier_thread, NULL, create_solder, (void *)1);
				break;
		}
	}

	pthread_mutex_destroy(&mutex);
	return 0;
}

void *create_solder(void * num){
	long soldiers_count = (long) num;
	if (soldiers_count == 1 && GOLD >= 10){
		print_msg("Soldier created!");
		pthread_mutex_lock(&mutex);
			SOLDIERS += 1;
			print_soldiers(SOLDIERS);
			GOLD -= 10;
			print_gold(GOLD);
		pthread_mutex_unlock(&mutex);
	} else if (soldiers_count == 10 && GOLD >= 100){
		print_msg("10 x soldier created!");
		pthread_mutex_lock(&mutex);
			SOLDIERS += 10;
			GOLD -= 100;
			print_gold(GOLD);
			print_soldiers(SOLDIERS);
		pthread_mutex_unlock(&mutex);
	} else{
		print_fail("Not enough gold!");
	}
	
}

void *create_miner(){
	if (GOLD >= 100){
		print_msg("Miner created!");
		pthread_mutex_lock(&mutex);
			GOLD -= 100;
			print_gold(GOLD);
		pthread_mutex_unlock(&mutex);
		while (1){
			pthread_mutex_lock(&mutex);
				GOLD += 10;
				print_gold(GOLD);
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}
	} else
	{
		print_fail("Not enough gold!");
	}
	
}

void *create_zombies(){
	while (1){
		for (int i = 5; i >= 0; --i){
			pthread_mutex_lock(&mutex);
				print_zombies(i, ZOMBIES);
			pthread_mutex_unlock(&mutex);
			sleep(1);
		}

		if (ZOMBIES > SOLDIERS){
			pthread_mutex_lock(&mutex);
				LIVES -= (ZOMBIES - SOLDIERS);
			pthread_mutex_unlock(&mutex);
			print_fail("Zombie attack succeded ;(!");
			if (LIVES <= 0) game_end(ZOMBIES);
			else {
				pthread_mutex_lock(&mutex);
					print_health(LIVES);
				pthread_mutex_unlock(&mutex);
			}
		}else {
			print_succ("Zombie attack deflected!:)");
		}

		pthread_mutex_lock(&mutex);
			ZOMBIES *= 2;
		pthread_mutex_unlock(&mutex);
	}
}