#include "unistd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    int result;
    int fd = open("dup.c", O_RDONLY);
    char buff[20];

    dup2(fd, STDIN_FILENO);

    execlp("wc", "wc", "-l", NULL);
    return 0;
}