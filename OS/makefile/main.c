#include <sys/types.h>
#include <unistd.h>
#include "fcntl.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define stdin_name "stdin"
#define o_header "==> "
#define c_header " <==\n"

void headers();
void readStdIn();
int myread_fd(int fd);
void mywrite(int count, int fd, int flag);
int myread_str(char *str);

int main(int argc, char const *argv[])
{
    if (argc == 1) readStdIn(); // zero argvs
    else {
        for (int i = 1; i < argc; ++i){
            if(i != 1) write(STDOUT_FILENO, "\n", 1); // writes \n before ==>
            if (strcmp(argv[i], "-") == 0){
                if (argc > 2) headers(stdin_name); // puts headers
                readStdIn();
            }
            else{
                int fd;
                if (argc > 2) headers(argv[i]); // puts headers
                fd = open(argv[i], O_RDONLY);
                mywrite(argc, fd, myread_fd(fd));
                close(fd);
            }
        }
    }
    return 0;
}


void headers(char* str){
    write(STDOUT_FILENO, o_header, strlen(o_header));
    write(STDOUT_FILENO, str, strlen(str));
    write(STDOUT_FILENO, c_header, strlen(c_header));
}


void readStdIn(){
    char buff;
    char str[256] = "\0";
    int status = 0, i = 0, nls;
    while ((status = read(STDIN_FILENO, &buff, 1)) != 0)
    {
        strcat(str, &buff);
    };
    nls = myread_str(str);
    while (nls > 10){
        if (str[i] == '\n') nls--;
        i++;
    }
    while (i < strlen(str)){
        write(STDOUT_FILENO, &str[i], 1);
        i++;
    }
}


int myread_str(char *str){
    int nls = 0, len = strlen(str);
    for (int i = 0; i < len; i++){
        if (str[i] == '\n') nls ++;
    }
    return nls;
}


int myread_fd(int fd){
    char buff;
    int status = -1;
    int nls = 0;
    while (read(fd, &buff, 1) != 0) if (buff == '\n') nls++; // counts \n
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
    while ((status = read(fd, &buff, 1)) != 0){ // writes everything left
        write(STDOUT_FILENO, &buff, status);
    }
    write(STDOUT_FILENO, "\n", 1);
}
