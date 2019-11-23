#include <sys/types.h>
#include <unistd.h>
#include "fcntl.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "stdio.h"

void readStdIn(int count);
int myread(int fd);
void mywrite(int count, int fd, int flag);

int main(int argc, char const *argv[])
{
    for (int i = 1; i < argc; ++i){
        if (atoi(argv[i]) == '-'){
            // read from stdin
            readStdIn(argc);
        }
        else{
            int fd;
            fd = open(argv[i], O_RDONLY);
            mywrite(argc, fd, myread(fd));
            close(fd);
        }
    }
    return 0;
}

void readStdIn(int count){
    char buff;
    int status = 0;
    while ((status = read(STDIN_FILENO, &buff, 1) != 0))
    {
        write(STDOUT_FILENO, &buff, status);
    }
    
}

int myread(int fd){
    char buff;
    int status = -1;
    int nls = 0;
    while (read(fd, &buff, 1) != 0){
        if (buff == '\n') nls++;
    }
    if (nls <= 10) return -1; // 10 or less lines
    return nls; // more than 10 lines
}

void mywrite(int count, int fd, int flag){
    char buff;
    int status = 0;
    lseek(fd, 0, SEEK_SET);
    while(flag >= 10){ // goes in if only flag > 10
        read(fd, &buff, 1);
        if (buff == '\n') flag--;
    }
    while ((status = read(fd, &buff, 1)) != 0){ // writes everything for all of them
        write(STDOUT_FILENO, &buff, status);
    }
    write(STDOUT_FILENO, "\n", status);
}
