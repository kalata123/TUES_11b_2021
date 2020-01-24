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
    char c;
    int status;
    pid_t pid;
    while (1)
    {
        char * str = (char *)malloc(sizeof(char));
        printf("$ ");
        do{
            c = fgetc(stdin);
            if (c == -1 || c == '\n') break;
            else{
                str[strlen(str)] = c;
                str = (char *)realloc(str, sizeof(char) *(strlen(str)+1));
            }
        } while (c != '\n');
        if (c == -1) break;
        str[strlen(str)] = '\0';
        char ** array = parse_cmdline(str);
        pid = fork();
        if (pid < 0){
            free(array);
            perror("fork");
        }else if (pid == 0){
            if(execvp(array[0], array) == -1){
                perror(array[0]);
                free(array);
                exit(-1);
            }
        }else{
            if (waitpid(pid, &status, 0) != pid){
                free(array);
                perror("");
            }
        }
        free(str);
        // free(*array);
        free(array);
    }
    return 0;
}