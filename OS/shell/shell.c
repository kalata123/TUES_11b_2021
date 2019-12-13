#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

char** parse_cmdline( const char* cmdline );

int main(int argc, char *argv[]) {
    pid_t pid;
    char c = 0;
    int status = 0;
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
        printf("%s\n", str);
        char **give = parse_cmdline(str);
        pid = fork();
        if (pid < 0){
            perror("fork");
        }else if (pid == 0){
            if(execvp(argv[1], &argv[1]) == -1){
                perror(argv[1]);
                exit(-1);
            }
        }else
        {
            if (waitpid(pid, &status, 0) != pid){
                perror("");
                exit(-1);
            }
        }
        free(str);
    }
    return 0;
}
char** parse_cmdline(const char* cmdline){
    char ** res = (char **) malloc(sizeof(char**));
    char tmp[200] = "\0";
    for (int i = 0, j = 0; i < strlen(cmdline); ++i, ++j){
        while (cmdline[i] != ' ')
        {
            tmp[strlen(tmp)] = cmdline[i];
            ++i;
            if (strlen(cmdline) <= i) break;
        }
        res = (char **)realloc(res, sizeof(char**)*(strlen(tmp)));
        strcpy(res[j], tmp);
        tmp[0] = '\0';
    }
    return res;
    free(*res);
    free(res);
}