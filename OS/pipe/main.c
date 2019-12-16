#include "string.h"
#include "unistd.h"
#include "stdio.h"
// with pipe we can comunicate between two proccesses 

int main() {

    int pipefd[2];
    char buff[200];
    char *message = "Hello world\n";
    pipe(pipefd);
    pid_t pid = fork();

    if (pid == 0){
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execlp("ls", "ls", "-l", NULL);
        close(pipefd[1]);
    }else if (pid > 0){
        int result;
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        while ((result = read(STDIN_FILENO, buff, 200)) > 0){
            write(STDOUT_FILENO, buff, result);
        }
        close(pipefd[0]);
        
    }else{
        perror("fork");
        return 1;
    }

    return 0;
}