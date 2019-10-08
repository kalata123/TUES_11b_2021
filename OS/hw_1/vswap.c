#include<stdio.h>
void swap(void* a, void* b, size_t size){
    unsigned char* c = a, *k = b, tmp;
    for(size_t i = 0; i < size; i++){
        tmp = c[i];
        c[i] = k[i];
        k[i] = tmp;
    }
}
