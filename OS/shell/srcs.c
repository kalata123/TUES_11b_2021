#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char** parse_cmdline( char* cmdline );

int main(int argc, char *argv[]) {
    pid_t pid;
    char c = 0;
    int status = 0;
    while (1)
    {
        int j = 0;
        char *tmp;
        const char key[2] = " ";
        char * str = (char *)malloc(sizeof(char));
        // char ** res;
        printf("$ ");

        do{
            c = fgetc(stdin);
            if (c == -1 || c == '\n') break;
            else{
                str[strlen(str)] = c;
                if (c == ' ') j++;
                str = (char *)realloc(str, sizeof(char) *(strlen(str)+1));
            }
        } while (c != '\n');
        if (c == -1) break;
        str[strlen(str)] = '\0';
        
        char ** res = parse_cmdline(str);//malloc(sizeof(char*));
        // j = 2;
        for (int i = 0; i < j; i++){
            write(STDOUT_FILENO, res[i], strlen(res[i]));
            write(STDOUT_FILENO, "\n", 1);
        }
        pid = fork();
        if (pid < 0){
            free(str);
            free(res);
            perror("fork");
        }else if (pid == 0){
            if(execvp(res[0], res) == -1){
                perror(res[0]);
                free(str);
                free(res);
                exit(-1);
            }
        }else
        {
            if (waitpid(pid, &status, 0) != pid){
                perror("");
            }
        }
        free(str);
        for (int i = 0; i < j; i++){
            free(res[i]);
        }
        free(res);
        res = NULL;
    }
    return 0;
}

char** parse_cmdline( char* cmdline ){
    char ** res = NULL;
    char *tmp;
    const char key[2] = " ";
    int j = 0;
    tmp = strtok(cmdline, key);
    while (tmp != NULL)
    {
        res = realloc(res, sizeof(char *)*(j+1));
        res[j] = tmp;
        j++;
        tmp = strtok(NULL, key);
    }
    res = realloc(res, sizeof(char*)*(j+1));
    res[j] = NULL;
    for (int i = 0; i < j; i++){
        write(STDOUT_FILENO, res[i], strlen(res[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return res;
}