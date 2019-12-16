#include "string.h"
#include "unistd.h"
#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// with pipe we can comunicate between two proccesses 

int main() {

    int pipefd[2];
    char buff[200];
    char *message = "Hello world\n";
    mkfifo("mkfifo", 0666);

    return 0;
}