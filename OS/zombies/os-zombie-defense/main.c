#include "ui.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *create_solder(void *);
void *create_miner(void *);
void *create_zombies();

int ZOMBIES = 1, SOLDIERS = 0, LIVES = 100, GOLD = 300;

pthread_mutex_t gold_mutex;
pthread_mutex_t soldiers_mutex;

int main() {
	init();
	print_gold(GOLD);
	print_soldiers(SOLDIERS);
	print_health(LIVES);

	pthread_mutex_init(&gold_mutex, NULL);
	pthread_mutex_init(&soldiers_mutex, NULL);

	pthread_t zombie_thread;
	pthread_create(&zombie_thread, NULL, create_zombies, NULL);

	while(1) {
		int ch = get_input();
		switch(ch) {
			case 'q':
				pthread_mutex_destroy(&gold_mutex);
				pthread_mutex_destroy(&soldiers_mutex);
				game_end(ZOMBIES);
				break;
			case 'n':;
				pthread_t miner_thread;
				if (GOLD >= 1000){
					pthread_mutex_lock(&gold_mutex);
					GOLD -= 1000;
					print_gold(GOLD);
					pthread_mutex_unlock(&gold_mutex);
					pthread_create(&miner_thread, NULL, create_miner, (void *) 10);
				} else print_fail("Not enough gold!");
				break;
			case 'm':;
				pthread_t x10_miner_thread;
				if (GOLD >= 100){
					pthread_mutex_lock(&gold_mutex);
					GOLD -= 100;
					print_gold(GOLD);
					pthread_mutex_unlock(&gold_mutex);
					pthread_create(&x10_miner_thread, NULL, create_miner, (void*) 1);
				} else print_fail("Not enough gold!");
				break;
			case 's':
				if (GOLD >= 10){
					print_msg("Soldier created!");

					pthread_mutex_lock(&gold_mutex);
						GOLD -= 10;
						print_gold(GOLD);
					pthread_mutex_unlock(&gold_mutex);
					
					pthread_mutex_lock(&soldiers_mutex);
						SOLDIERS += 1;
						print_soldiers(SOLDIERS);
					pthread_mutex_unlock(&soldiers_mutex);

				} else print_fail("Not enough gold!"); 
				break;
			case 'x':
				if (GOLD >= 100){
					print_msg("10 x soldier created!");

					pthread_mutex_lock(&gold_mutex);
					GOLD -= 100;
					print_gold(GOLD);
					pthread_mutex_unlock(&gold_mutex);

					pthread_mutex_lock(&soldiers_mutex);
					SOLDIERS += 10;
					print_soldiers(SOLDIERS);
					pthread_mutex_unlock(&soldiers_mutex);

				} else print_fail("Not enough gold!"); 
				break;
			case 'z':
				if (GOLD >= 1000){
					print_msg("100 x soldier created!");

					pthread_mutex_lock(&gold_mutex);
					GOLD -= 1000;
					print_gold(GOLD);
					pthread_mutex_unlock(&gold_mutex);

					pthread_mutex_lock(&soldiers_mutex);
					SOLDIERS += 100;
					print_soldiers(SOLDIERS);
					pthread_mutex_unlock(&soldiers_mutex);

				} else print_fail("Not enough gold!"); 
				break;
		}
	}

	pthread_mutex_destroy(&gold_mutex);
	pthread_mutex_destroy(&soldiers_mutex);
	return 0;
}

// void *create_solder(void * num){
// 	long soldiers_count = (long) num;
// 	if (soldiers_count == 1 && GOLD >= 10){
// 		print_msg("Soldier created!");

// 		pthread_mutex_lock(&soldiers_mutex);
// 			SOLDIERS += 1;
// 			print_soldiers(SOLDIERS);
// 		pthread_mutex_unlock(&soldiers_mutex);

// 		pthread_mutex_lock(&gold_mutex);
// 			GOLD -= 10;
// 			print_gold(GOLD);
// 		pthread_mutex_unlock(&gold_mutex);

// 	} else if (soldiers_count == 10 && GOLD >= 100){
// 		print_msg("10 x soldier created!");

// 		pthread_mutex_lock(&soldiers_mutex);
// 		SOLDIERS += 10;
// 		print_soldiers(SOLDIERS);
// 		pthread_mutex_unlock(&soldiers_mutex);

// 		pthread_mutex_lock(&gold_mutex);
// 		GOLD -= 100;
// 		print_gold(GOLD);
// 		pthread_mutex_unlock(&gold_mutex);

// 	} else print_fail("Not enough gold!");
// }

void *create_miner(void * num){
	long miners = (long) num;
	print_msg(miners >= 1 ? "10 x miners created!" : "Miner created");
	while (1){
		pthread_mutex_lock(&gold_mutex);
		GOLD += 10*miners;
		print_gold(GOLD);
		pthread_mutex_unlock(&gold_mutex);
		sleep(1);
	}
	
}

void *create_zombies(){
	while (1){
		for (int i = 5; i >= 0; --i){
			print_zombies(i, ZOMBIES);
			sleep(1);
		}

		pthread_mutex_lock(&soldiers_mutex);
		if (ZOMBIES > SOLDIERS){
				LIVES -= (ZOMBIES - SOLDIERS);
				print_fail("Zombie attack succeded ;(!");
			if (LIVES <= 0){
				pthread_mutex_destroy(&gold_mutex);
				pthread_mutex_destroy(&soldiers_mutex);
				game_end(ZOMBIES);
			}
			else print_health(LIVES);
		}else {
			print_succ("Zombie attack deflected!:)");
		}
		pthread_mutex_unlock(&soldiers_mutex);

		ZOMBIES *= 2;
	}
}
