#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
    char status;
    // system("@cls||clear");
    system("@cls||clear");
    do{
        scanf("%c", &status);
        printf("asd");
        if (status == 'e') {
            break;
            // status = 1;
        }
        else if (status == 'p')
        {
            // status = 1;
            continue;
        }else if (status != 'p' || status != 'e')
        {
            printf("Supported commands:\np N - Starts a new calculation for the number of primes from 1 to N\ne - Waits for all calculations to finish and exits\n");
        }
        
        // getchar();
    }while(status != 'e');
    return 0;
}
