#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct dirent dirent_t;
typedef struct stat stat_t;

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
    printf("%-6s %-6s %-10s\n", "uid", "size", "dir name");
    while ((dircontent = readdir(dir)) != NULL) {
        if ((strcmp(dircontent->d_name, "..") != 0) && (strcmp(dircontent->d_name, ".") != 0)) {
            if (stat(dircontent->d_name, &statcontent) == -1) {
                perror("stat");
                return -1;
            }
            printf("%-6u ", statcontent.st_uid);
            printf("%-6ld ", statcontent.st_size);
            printf("%-10s \n", dircontent->d_name);
        }
    }

    if (closedir(dir) == -1) {
        perror("closedir");
        return -1;
    }
    return 0;
}