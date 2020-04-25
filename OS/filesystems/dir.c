#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef struct dirent dirent_t;
typedef struct stat stat_t;

char *formatdate(char *str, time_t val);

int main(int argc, char **argv) {
    DIR *dir = opendir(".");
    if (argc == 2) {
        dir = opendir(argv[1]);
    }
    if (dir == NULL) {
        perror("opendir");
        return -1;
    }

    dirent_t *dircontent;
    stat_t statcontent;
    printf("%-20s", "Access Time");
    printf("%-6s", "Uid");
    printf("%-6s", "Size");
    printf("%-10s\n", "Name");
    while ((dircontent = readdir(dir)) != NULL) {
        // exlude the pointers
        if ((strcmp(dircontent->d_name, "..") != 0) && (strcmp(dircontent->d_name, ".") != 0)) {

            // get the status of the current object
            if (stat(dircontent->d_name, &statcontent) == -1) {
                perror("stat");
                return -1;
            }

            // check flags
            char *flags = "la";

            char str[36];
            printf("\033[0;34m");
            printf("%-20s", formatdate(str, statcontent.st_atime));
            printf("\033[0m");

            printf("\033[0;31m");
            printf("%-6u", statcontent.st_uid);
            printf("\033[0m");

            printf("\033[0;32m");
            printf("%-6ld", statcontent.st_size);
            printf("\033[0m");

            // print colorized name

            if (S_ISDIR(statcontent.st_mode)) {
                printf("\033[1;32m");
                printf("%-10s\n", dircontent->d_name);
                printf("\033[0m");
            } else {
                printf("\033[0;33m");
                printf("%-10s", dircontent->d_name);
                printf("\033[0m");
            }
            printf("\n");
        }
    }

    if (closedir(dir) == -1) {
        perror("closedir");
        return -1;
    }
    return 0;
}

char *formatdate(char *str, time_t val) {
    strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
    return str;
}