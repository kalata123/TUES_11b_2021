#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

int spcs = 0;

char** parse_cmdline( const char* cmdline );

int main(int argc, char *argv[]) {
    pid_t pid;
    char c = 0;
    int status = 0;
    while (1)
    {
        char *tmp;
        const char key[2] = " ";
        char * str = (char *)malloc(sizeof(char));
        printf("$ ");

        do{
            c = fgetc(stdin);
            if (c == -1 || c == '\n') break;
            else{
                if (c == ' ') spcs++;
                str[strlen(str)] = c;
                str = (char *)realloc(str, sizeof(char *) *(strlen(str)+1));
            }
        } while (c != '\n');
        if (c == -1) break;
        str[strlen(str)] = '\0';

        char ** res = malloc(sizeof(char*)*spcs);

        int j = 0;
        tmp = strtok(str, key);
        while (tmp != NULL)
        {to
            res[j] = realloc(res, sizeof(char *)*strlen(tmp));
            res[j] = tmp;
            j++;
            tmp = strtok(NULL, key);
        }
        // res = realloc(res, sizeof(char*)*spcs);
        // res[j] = NULL;

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
                // free(*res);
                exit(-1);
            }
        }else
        {
            if (waitpid(pid, &status, 0) != pid){
                perror("");
            }
        }

        free(str);
        for (int i = 0; res[i] != NULL; i++){
            free(res[i]);
        }
        free(res);
    }
    return 0;
}

char** parse_cmdline( const char* cmdline ){
    // char ** res = NULL;
    char *tmp;
    const char key[2] = " ";
    char *res[20] = "\0";
    char myString[strlen(cmdline)];
    strcpy(myString, cmdline);
    printf("%s\n%s\n", myString, cmdline);
    tmp = strtok(cmdline, key);
    int j = 0;
    while (tmp != NULL)
    {
        // res = realloc(res, sizeof(char *) * (j+1));
        res[j] = tmp;
        j++;
        tmp = strtok(NULL, key);
    }
    res = realloc(res, sizeof(char*)*(j+1));
    res[j] = NULL;
    printf("res|%s|\n",res[0]);
    return res;
}