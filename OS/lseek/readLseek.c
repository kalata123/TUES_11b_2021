#include <sys/types.h>
#include <unistd.h>
#include "fcntl.h"
#include "sys/stat.h"

typedef struct {
    char data;
    unsigned char next;
}block_t;

int main(int argc, char const *argv[])
{
    int w_fd = open(argv[1], O_RDONLY);
    int status;
    block_t bl;
    while ((status = read(w_fd, &bl, 2)) != 0){
        if (bl.next == 0) break;
        write(STDOUT_FILENO, &bl.data, 1);
        lseek(w_fd, bl.next, SEEK_SET);
    }
    write(STDOUT_FILENO, "\n", 1);
    close(w_fd);
    return 0;
}
