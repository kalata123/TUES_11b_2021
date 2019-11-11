#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"

int main(){
    int fd = open("read10lines.c", O_RDONLY);
    char buff[200];
    int status;
    int nls = 0;
    while ((status = read(fd, buff, 200)) != 0){
        int written = 0;
        while (written < status)
        {
            for (int i = 0; i < 200; i++){
                if (buff[i] == '\n') ++nls;
            }
            written += write(fd, buff, status - written);
        }
        
    }
    return 0;
}