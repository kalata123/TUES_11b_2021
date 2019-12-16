#include "string.h"
#include "unistd.h"
#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sys/wait.h"
// with pipe we can comunicate between two proccesses 

int main() {

    int pipefd[2], status;
    char buff[200];
    char *message = "Hello world\n";
    mkfifo("mkfifo", 0666);
    int fd = open("mkfifo", O_WRONLY);
    while((status = read(STDIN_FILENO, buff, 200)) != 0){
        write(STDOUT_FILENO, buff, status);
    }
    close(fd);

    return 0;
}