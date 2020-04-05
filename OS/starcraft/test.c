#include "stdio.h"
#include "stdlib.h"


int main() {

    int a = 0;
    printf("%d\n", !!a);

    // int *a = (int *)malloc(sizeof(int));
    // a[0] = 2;
    // printf("a = %d\n", a[0]);
    // a = (int *)realloc(a, sizeof(int)+1);
    // a[1] = 3;
    // printf("a1 = %d a2= %d\n", a[0], a[1]);
    // int empty_mineral_blocks[2]; // if any block is 1 - it is empty
    // memset(empty_mineral_blocks, 0, 2*sizeof(int));
    // for (int i = 0; i < 2; ++i){
    //     printf("%d\n", empty_mineral_blocks[i]);
    // }
    return 0;
}