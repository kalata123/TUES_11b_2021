#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char** parse_cmdline( const char* cmdline );

char** parse_cmdline( const char* cmdline ){
    /*int count_spcs = 0;
    char line[strlen(cmdline)];
    strcpy(line, cmdline);
    for (int i = 0; i < strlen(cmdline); i++){
        if (cmdline[i] == ' ') count_spcs++;
    }
    char ** array;
    char *val;
    array = malloc(sizeof(char *) * (count_spcs + 2));

    val = strtok(line, " ");
    int i = 0;
    while (val != NULL){
        array[i] = val;
        i++;
        val = strtok(NULL, " ");
    }
    array[i] = NULL;
    return array;*/
    // -----------------------------------
    char str[strlen(cmdline)];
    strcpy(str, cmdline);
    int j = 0;
    char ** res = malloc(sizeof(char*));
    char *tmp;
    const char key[2] = " ";
    tmp = strtok(str, key);
    while (tmp != NULL)
    {
        res = realloc(res, sizeof(char *)*(j+1));
        res[j] = tmp;
        j++;
        tmp = strtok(NULL, key);
    }
    res = realloc(res, sizeof(char*)*(j+1));
    res[j] = NULL;
    return res;
}

int main(int argc, char *argv[]) {
    char str[1024];
    while (1)
    {
        if (fgets(str, 1024, stdin) == NULL) exit(1);
        printf("%s\n", str);
    }
    return 0;
}