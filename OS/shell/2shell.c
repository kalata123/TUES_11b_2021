#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char** parse_cmdline( const char* cmdline );

char** parse_cmdline( const char* cmdline ){
    int count_spcs = 0;
    char line[strlen(cmdline)];
    strcpy(line, cmdline);
    for (int i = 0; i < strlen(cmdline); i++){
        if (cmdline[i] == ' ') count_spcs++;
    }
    char ** array = malloc(sizeof(char *) * (count_spcs + 1));
    printf("%d\n", count_spcs);
    char *val;

    val = strtok(line, " ");
    int i = 0;
    char *tmp;
    while (val != NULL){
        array[i] = malloc(sizeof(char *) * strlen(val));
        printf("%ld\n", sizeof(val));
        write(STDOUT_FILENO, val, strlen(val));
        array[i] = val;
        printf("%ld\n", sizeof(array[i]));
        write(STDOUT_FILENO, array[i], strlen(array[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
        val = strtok(NULL, " ");
    }
    // for (; i >= 0; i--){
    //     printf("%ld\n", sizeof(array[i]));
    // }
    
}

int main(int argc, char *argv[]) {
    // write(STDOUT_FILENO, "1", 1);
    char *str = "Hello from the other side";
    parse_cmdline(str);
    return 0;
}