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

#define err_open_1 "tail: cannot open '"
#define err_open_2 "' for reading"

#define err_read_1 "tail: error reading '"
#define err_read_2 "'"

#define err_write_1 "tail: error writing '"
#define err_write_2 "'"

#define err_close_1 "tail: error reading '"
#define err_close_2 "': Input/output error\n"

int err = 0;

int handle_error(char error, const char *name){
    //------------------------------------------------------------------------
    // FUNCTION: handle_error
    // Deals with errors
    // PARAMETERS:
    // error - char used to show the kind of error
    // namе - the name of the file - used when printing the errors
    //------------------------------------------------------------------------
    char msg[200] = "\0";
    switch (error){
        case 'r':
            /* read err */
            strcat(msg, err_read_1);
            strcat(msg, name);
            strcat(msg, err_read_2);
            perror(msg);
            err = 1;
            return 0;
            break;
        case 'w':
            /* write err */
            strcat(msg, err_write_1);
            strcat(msg, name);
            strcat(msg, err_write_2);
            perror(msg);
            err = 1;
            return 0;
            break;
        case 'c':
            /* close err */
            write(STDERR_FILENO, err_close_1, strlen(err_close_1));
            write(STDERR_FILENO, name, strlen(name));
            write(STDERR_FILENO, err_close_2, strlen(err_close_2));
            err = 1;
            return 0;
            break;
        case 'o':
            /* open err */
            strcat(msg, err_open_1);
            strcat(msg, name);
            strcat(msg, err_open_2);
            perror(msg);
            err = 1;
            return 0;
            break;

        default:
            break;
    }
}

int putHeader(const char* name){
    //------------------------------------------------------------------------
    // FUNCTION: putHeader
    // it's writing the headers before the actual output
    // PARAMETERS:
    // name - the name of the file - used in the header and in error handling
    //------------------------------------------------------------------------
    int status;
    status = write(STDOUT_FILENO, o_header, strlen(o_header));
    if (status == -1) return handle_error('w', name);
    write(STDOUT_FILENO, name, strlen(name));
    if (status == -1) return handle_error('w', name);
    write(STDOUT_FILENO, c_header, strlen(c_header));
    if (status == -1) return handle_error('w', name);
    return 1;
}

int workFromStdin(int argc, const char *name, int flag){
    //------------------------------------------------------------------------
    // FUNCTION: workFromStdin
    // it does all the logic behind working from stdin
    // PARAMETERS:
    // argc - integer - used when putting headers
    // name - the name of the file - used in the header and in error handling
    // flag - integer - used when for the correct output 
    //------------------------------------------------------------------------
    char *str = (char*)malloc(sizeof(char)); // with valgrind gives some errors
    // char str[5000] = "\0";
    char buff;
    int status = 0, nls = 0, i = 0;
    if (flag > 1 && err != 1) write(STDOUT_FILENO, "\n", 1);
    if (argc > 2) putHeader(name);
    while ((status = read(STDIN_FILENO, &buff, 1)) != 0)
    {
        if (status == -1) return handle_error('r', name);
        str = (char*)realloc(str, sizeof(char) * strlen(str)+1);
        strcat(str, &buff);
    }
    for (i = 0; i < strlen(str); ++i) if (str[i] == '\n') nls++;
    for (i = 0; nls >= 11; ++i){
        if (str[i] == '\n') nls--;
    }
    for (int tmp = strlen(str), er = 0; i < tmp; ++i){
        while (1)
        {
            status = write(STDOUT_FILENO, &str[i], 1);
            if (status == -1) return handle_error('w', name);
            if (status != 0) break;
        }
    }
    err = 0;
    free(str);
}

int newLines(int fd, const char *name){
    //------------------------------------------------------------------------
    // FUNCTION: newLines
    // Counts the new lines using file descriptor
    // PARAMETERS:
    // fd - integer - used for reading
    // name - the name of the file - used  in error handling
    //------------------------------------------------------------------------
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
    //------------------------------------------------------------------------
    // FUNCTION: workFromFile
    // it does all the logic behind working from file
    // PARAMETERS:
    // argc - integer - used when putting headers
    // name - the name of the file - used in the header and in error handling
    // flag - integer - used when for the correct output 
    //------------------------------------------------------------------------
    int fd, nls, status_r = 0, status_w, status_o;
    char buff;
    fd = open(string, O_RDONLY);
    if (fd == -1) return handle_error('o', string); //open err
    if (flag > 1 && err == 0) status_w = write(STDOUT_FILENO, "\n", 1);
    if (status_w == -1) return handle_error('w', string); //open err
    if (argc > 2) putHeader(string);

    /*Logic{*/
    nls = newLines(fd, string);  //count \n
    lseek(fd, 0, SEEK_SET); // set read to the beginning
    if (nls == -1) { // some error during \n counting
        return 0;
    }
    else{
        while(nls >= 11){ // read
            status_r = read(fd, &buff, 1);
            if (status_r == -1) return handle_error('r', string); // read err
            if (buff == '\n') nls--;
        }

        while ((status_r = read(fd, &buff, 1)) != 0){
            if (status_r == -1) return handle_error('r', string); // read err
            while (1)
            {
                status_w = write(STDOUT_FILENO, &buff, status_r);
                if (status_w != 0) break;
            }
            
            if (status_w == -1) return handle_error('w', string); // write err
        }
        err = 0;
    }
    /*}Logic*/
    status_o = close(fd);
    if (status_o == -1) return handle_error('c', string); // close err
    return 1;
}

int main(int argc, char const *argv[]){
    //------------------------------------------------------------------------
    // FUNCTION: main
    // it's the trigger of the real work
    // PARAMETERS:
    // argc - integer - count of argv
    // argv - all console arguments
    //------------------------------------------------------------------------
    int result;
    if (argc == 1){
        //read from stdin
        workFromStdin(argc, stdin_name, 1);
        return 0;
    }
    for (int i = 1; i < argc; ++i){
        if (!strcmp(argv[i],"-")) {
            //read from stdin
            workFromStdin(argc, stdin_name, i);
            continue;
        }else{
            result = workFromFile(argc, argv[i], i);
            if (result == 0) continue;
        }
    }
    return 0;
}
