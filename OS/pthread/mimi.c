#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *my_thread(void *);
void *one_thread();

int main() {
    pthread_t thread1, threadX10[5];

    for (long i = 0; i < 5; i++){
        pthread_create(&threadX10[i], NULL, my_thread, (void *) i+1);
    }

    pthread_create(&thread1, NULL, one_thread, NULL);

    pthread_join(thread1, NULL);

    for (int i = 0; i < 5; ++i){
        pthread_join(threadX10[i], NULL);
    }

    printf("All good\n");

    return 0;

}

void *my_thread(void *id){
    for (int i = 0; i < 3; ++i){
        // sleep(1);
        printf("%ld listening in maths - %d\n", (long) id, i);
        sleep(2);
    }
    printf("Good to go\n");
    return NULL;
}

void *one_thread(){
    for (int i = 0; i < 4; ++i){
        printf(i > 2 ? "Hehe, 3ka li? HAHAHAHAHAH\n" : "Hmmmm\n");
    }
    return NULL;
}