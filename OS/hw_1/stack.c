#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    size_t size;
    size_t capacity;
    int *elements;
} stack;

void stack_init(stack *s){
    s->elements = NULL;
    s->size = 0;
    s->capacity = 0;
}
void stack_destroy(stack *s){
    free(s->elements);
}

int stack_empty(stack *s){
    if(s->size<=0){
        return 1;
    }
    return 0;
}
void stack_push(stack *s, int val){
    s->elements = (int *)realloc(s->elements, sizeof(int)*(++s->size));
    s->elements[s->size-1] = val;
}
int stack_top(stack *s){
    return s->elements[s->size-1];
}
void stack_pop(stack *s){
    s->elements = (int *)realloc(s->elements, sizeof(int) * (--s->size));
}





