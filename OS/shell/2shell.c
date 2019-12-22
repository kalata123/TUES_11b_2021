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
    char ** array = malloc(sizeof(char *) * (count_spcs +  2));
    char *val;

    val = strtok(line, " ");
    int i = 0;
    while (val != NULL){
        array[i] = val;
        i++;
        val = strtok(NULL, " ");
    }
    return array;
}

int main(int argc, char *argv[]) {
    char *str = "Hello from the other side";
    char ** array;
    array = parse_cmdline(str);
    int i = 5;
    for (i = 4; i >= 0; i--){
        do{}while (write(STDOUT_FILENO, *(array+ i), strlen(*(array + i))) == 0);
        do{}while (write(STDOUT_FILENO, " ", 1) == 0);
    }
    free(array);
    return 0;
}