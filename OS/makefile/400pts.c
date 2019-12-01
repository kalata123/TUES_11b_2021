//------------------------------------------------------------------------
// NAME: Kaloyan Angelov
// CLASS: XIb
// NUMBER: 15
// PROBLEM: #1
// FILE NAME: main.c (unix file name)
// FILE PURPOSE:
// Implementing user command tail
// Using only read/write
//------------------------------------------------------------------------
#include <sys/types.h>
#include <unistd.h>
#include "fcntl.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#define stdin_name "standard input"
#define o_header "==> "
#define c_header " <==\n"

void headers();
void readStdIn();
int myread_fd(int);
int mywrite(int, int, int, const char*);
int myread_str(char*);

int errs = 0;       
int main(int argc, char const *argv[])
{
    if (argc == 1) {
        readStdIn();
        return 0;
    } // no args
    for (int i = 1; i < argc; ++i){
        if (strcmp(argv[i], "-") == 0){
            if (i > 1 && errs < 1) write(STDOUT_FILENO, "\n", 1); // writes \n before ==>
            if (argc > 2) headers(stdin_name); // puts headers
            readStdIn();
            errs = 0;
            continue;
        }
        else{
            int fd;
            fd = open(argv[i], O_RDONLY);
            if (fd < 0){
                int cnt = 36+strlen(argv[i]);
                char er[cnt];
                strcat(er, "tail: cannot open '");
                strcat(er, argv[i]);
                strcat(er, "' for reading");
                perror(er);
                errs++;
            }else{
                if(errs < 1 && i > 1) write(STDOUT_FILENO, "\n", 1); // writes \n before ==>
                if (argc > 2) headers(argv[i]); // puts headers
                mywrite(argc, fd, myread_fd(fd), argv[i]);
                close(fd);
                errs = 0;
            }
        }
    }
    return 0;
}


void readStdIn(){
    char buff;
    char *str = (char*)malloc(sizeof(char)); // not working properly 
    // char str[8000] = "\0";
    int status = 0, i = 0, nls;
    while ((status = read(STDIN_FILENO, &buff, 1)) > 0)
    {
        str = (char*)realloc(str, sizeof(char) * strlen(str)+1);// seems it is not working for seq 1 10000
        strcat(str, &buff);
    }
    nls = myread_str(str);
    while (nls >= 11){
        if (str[i] == '\n') nls--;
        i++;
    }
    while (i < strlen(str)){
        write(STDOUT_FILENO, &str[i], 1);
        i++;
    }
    // free(str);
}


int mywrite(int count, int fd, int nls, const char* name){
    char buff;
    int status = 0;
    status = read(fd, &buff, 1);
    if (status == -1){
        write(STDERR_FILENO, "tail: error reading '", 21);
        write(STDERR_FILENO, name, strlen(name));
        write(STDERR_FILENO, "': Is a directory\n", 15);
        perror("");
        errs++;
        return -1;
    }
    lseek(fd, 0, SEEK_SET);
    while(nls >= 11){ // goes in if only flag > 10
        status = read(fd, &buff, 1);
        if (status == -1){
            write(STDERR_FILENO, "tail: error reading '", 21);
            write(STDERR_FILENO, name, strlen(name));
            write(STDERR_FILENO, "': Is a directory\n", 15);
            perror("");
            errs++;
            break; 
        }
        if (buff == '\n') nls--;
    }
    while ((status = read(fd, &buff, 1)) != 0){ // writes everything left
        write(STDOUT_FILENO, &buff, status);
    }
}


void headers(char* str){
    write(STDOUT_FILENO, o_header, strlen(o_header));
    write(STDOUT_FILENO, str, strlen(str));
    write(STDOUT_FILENO, c_header, strlen(c_header));
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
