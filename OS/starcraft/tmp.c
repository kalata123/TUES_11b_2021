#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void dos();
void *sod();
int count = 5;
typedef struct {
    long id;
    char name[256];
} person_t;

typedef struct {
    unsigned int count;
    person_t *people;
} jam_t;

jam_t jam;
int curr = 10;

pthread_t my_thread;

int main(int argc, char const *argv[])
{
    jam.count = 10;
    jam.people = malloc(sizeof(person_t) * jam.count);
    for (int i = 0; i < jam.count; ++i){
        jam.people[i].id = i;
        strcpy(jam.people[i].name, "ma name");
    }
    create_thread(&my_thread, NULL, sod, NULL);
    char ch;
    while(scanf("%c", &ch) != EOF){
        if (ch == 'd'){
            dos();
        } else if (ch == 'q'){
            break;

        }
    }

    for(int i = 0; i < curr; ++i)
        printf("total count is %u and %s has id %ld\n", jam.count, jam.people[i].name, jam.people[i].id);

    return 0;
}

void dos() {
    if (curr == jam.count){
        jam.people = realloc(jam.people, sizeof(person_t) * (jam.count * 2));
        jam.count *= 2;
    }
    strcpy(jam.people[curr].name, "hell name");
    jam.people[curr].id = curr;
    curr += 1;
}

void *sod(){
    while (1){
        for (int i = 0; i < jam.count; ++i){
            
        }
    }
}