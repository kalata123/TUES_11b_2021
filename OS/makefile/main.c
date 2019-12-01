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

int workFromStdin(int argc, int flag){

}

void headers(const char* str){
    write(STDOUT_FILENO, o_header, strlen(o_header));
    write(STDOUT_FILENO, str, strlen(str));
    write(STDOUT_FILENO, c_header, strlen(c_header));
}

int handle_error(char error, const char *name){
    switch (error){
        case 'r':
            /* read err */

            return 0;
        case 'w':
            /* write err */
            return 0;
        case 'c':
            /* close err */
            return 0;
        case 'o':

            /* open err */
            return 0;

        default:
            break;
    }
}

int newLines(int fd, const char *name){
    int nls = 0, status_r;
    char buff;
    lseek(fd, 0, SEEK_SET);
    while((status_r = read(fd, &buff, 1)) != 0){ // read
        if (status_r == -1){ // error occured
            handle_error('r', name);
            return -1;
        }
        if (buff == '\n') nls++;
    }
    return nls;
}

int workFromFile(int argc, const char *string, int flag){
    int fd, nls, status_r, status_w, status_o;
    char buff;
    fd = open(string, O_RDONLY);
    // lseek(fd, 0, SEEK_SET);
    // if (fd == -1) return handle_error('o', string); //open err
    if (flag > 1) write(STDOUT_FILENO, "\n", 1);/*print \n*/;
    if (argc > 1) headers(string)/*put header*/;

    /*Logic{*/
    nls = newLines(fd, string);  //count \n
    lseek(fd, 0, SEEK_SET); // set read to the beginning
    if (nls == -1) { // some error during \n counting
        return 0;
    }
    else if (nls <= 10){
        //start reading
        while((status_r = read(fd, &buff, 1)) != 0){ // read
            // if (status_r == -1) return handle_error('r', string); // read err
            //write everything
            status_w = write(STDOUT_FILENO, &buff, status_r);
            // if (status_w == -1) return handle_error('w', string); // write err
        }
    }else {
        //start reading
        while(nls >= 11){ // read
            status_r = read(fd, &buff, 1);
            // if (status_r == -1) return handle_error('r', string); // read err
            if (buff == '\n') nls--;
            /*Check for close error - return -1*/
        }
        while (status_r = read(fd, &buff, 1) != 0){
            // if (status_r == -1) return handle_error('r', string); // read err
            status_w = write(STDOUT_FILENO, &buff, status_r);
            // if (status_w == -1) return handle_error('w', string); // write err
        }
    }
    /*}Logic*/
    fd = close(fd);
    // if (fd == -1) return handle_error('c', string); // close err
    return 1;
}

int main(int argc, char const *argv[])
{
    int result;
    if (argc == 1){
        //read from stdin
        return 0;
    }
    for (int i = 1; i < argc; ++i){
        if (!strcmp(argv[i],"-")) {
            //read from stdin
        }else{
            result = workFromFile(argc, argv[i], i);
            // if result is -1 => an error occured 
            if (!result) continue;
        }
    }
    return 0;
}
