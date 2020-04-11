#include <stdio.h>

long scvs = 5;


int main() {
    printf("scvs = 5 + 1 = 6 || ++scvs = 6 || scvs++ = 7\n");
    printf("scvs = %ld + 1 = %ld || ++scvs = %ld || scvs++ = %ld\n", scvs, scvs + 1, ++scvs, scvs++);
    return 0;
}