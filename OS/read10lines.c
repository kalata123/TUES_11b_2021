#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"
#include "string.h"

void mywrite(int fd){
    char buff;
    int status;
    int nls = 0;
    while (nls < 10){
        status = read(fd, &buff, 1);
        if (buff == '\n') nls++;
        write(STDOUT_FILENO, &buff, status);
    }
}

int main(int argc, char *argv[])
{
    int fd;
    for(int i = 1; i < argc; ++i){
        if(i != 1) write(STDOUT_FILENO, "\n", 1);
        fd = open(argv[i], O_RDONLY);
        if(argc > 2){
            write(STDOUT_FILENO, "==> ", 4);
            write(STDOUT_FILENO, argv[i], strlen(argv[i]));
            write(STDOUT_FILENO, " <==\n", 5);
        }
        mywrite(fd);
    }
    return 0;
}
