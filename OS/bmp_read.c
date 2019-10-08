#include <stdio.h>
#include "stdlib.h"
#include <stdint.h>

void *read_image( const char *filepath );

int main(int argc, char const *argv[])
{
    read_image(argv[0]);
    return 0;
}

void *read_image(const char *filepath){
    FILE *fptr;
    fptr = fopen(filepath, "r");
    if (!fptr) return NULL;
    uint32_t read_data[100];
    uint32_t res;
    fread(read_data, sizeof(read_data), 1, fptr);
    printf("1\n");
    // puts(read_data);
    printf("%d\n",read_data[19]);  

}