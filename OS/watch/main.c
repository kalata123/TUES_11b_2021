#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "string.h"
#include "stdio.h"

int main(int argc, char **argv) {
    pid_t pid;
    int status = 0;
    while (1)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
        }else if (pid == 0)
        {
            if(execvp(argv[1], &argv[1]) == -1){
                perror(argv[1]);
                return 1;
            }
        }else
        {
            if (waitpid(pid, &status, 0) != pid){
                perror("");
                return 1;
            }
            sleep(2);
            
        }

    }
    return 0;
}