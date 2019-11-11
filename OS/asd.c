#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"

int main(int argc, char const *argv[]){
    int fd = open("a.txt", O_RDONLY);
    char buff[200];
    int status, nls = 0, ind;
    while ((status = read(fd, buff, 200)) != 0){
        int written = 0;
        while (written < status)
        {
            for (int i = 0; i < status; i++){
                if (buff[i] == '\n') ++nls;
                if (nls >= 10){
                    ind = i;
                    break;
                }
            }
            write(STDOUT_FILENO, buff, ind);
            if (nls >= 10){
                break;
            }
        }
    }
    close(fd);
    printf("\n");
    return 0;
}