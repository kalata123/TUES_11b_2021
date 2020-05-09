#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FLAGS "lRA"

typedef struct dirent dirent_t;
typedef struct stat stat_t;
typedef struct passwd passwd_t;
typedef struct group group_t;

char *formatdate(char *str, time_t val);
void colorize(char clr[2], int bold);
int scan_dir(DIR *dir, int argc, char **argv, char *name);
int is_chr_in_str(char *, char);
char get_file_type(mode_t type);
void print_date();

int main(int argc, char **argv) {

    DIR *dir = NULL;
    int val = 1;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] != '-') {
                val = 0;
                if ((dir = opendir(argv[i])) == NULL) {
                    perror("opendir");
                    return -1;
                }
                scan_dir(dir, argc, argv, ".");
                if (closedir(dir) == -1) {
                    perror("closedir");
                    return -1;
                }
            } else {
                val = 1;
            }
        }
    }
    if (val) {
        dir = opendir(".");
        scan_dir(dir, argc, argv, ".");
        if (closedir(dir) == -1) {
            perror("closedir");
            return -1;
        }
    }

    return 0;
}

int scan_dir(DIR *dir, int argc, char **argv, char *name) {

    /* get all flags in one string */
    // ->
    int i = 0, checker = 0;
    char option;
    char flags[4] = {0};

    while ((option = getopt(argc, argv, FLAGS)) != -1) {
        for (i = 0, checker = 1; i < strlen(flags); i++) {
            if (flags[i] == option) {

                checker = 0;
                break;
            }
        }
        if (checker) {
            if (is_chr_in_str(FLAGS, option)) {
                flags[i] = option;
            }
        }
        flags[3] = '\0';
    }
    // <-

    /* for each dir get its info and do stuff */
    // ->
    unsigned int total_blocks = 0;
    if (is_chr_in_str(flags, 'R')) {
        printf("%s:\n", name);
    }
    dirent_t *dirinfo;
    errno = 0;
    while ((dirinfo = readdir(dir)) != NULL) {
        stat_t statinfo;
        if (stat(dirinfo->d_name, &statinfo) == -1) {
            perror("stat");
            return -1;
        }

        // skip procces if . or .. and flagg is not 'a'
        if ((((strcmp(dirinfo->d_name, "..") == 0) ||
              (strcmp(dirinfo->d_name, ".") == 0)) &&
             !is_chr_in_str(flags, 'a')) ||
            (dirinfo->d_name[0] == '.' &&
             !is_chr_in_str(flags, 'A'))) {
            continue;
        } else {

            total_blocks += statinfo.st_blocks;
        }

        if (is_chr_in_str(flags, 'l')) {
            // print all things
            printf("%c", get_file_type(statinfo.st_mode));
            printf((statinfo.st_mode & S_IRUSR) ? "r" : "-");
            printf((statinfo.st_mode & S_IWUSR) ? "w" : "-");
            printf((statinfo.st_mode & S_IXUSR) ? "x" : "-");
            printf((statinfo.st_mode & S_IRGRP) ? "r" : "-");
            printf((statinfo.st_mode & S_IWGRP) ? "w" : "-");
            printf((statinfo.st_mode & S_IXGRP) ? "x" : "-");
            printf((statinfo.st_mode & S_IROTH) ? "r" : "-");
            printf((statinfo.st_mode & S_IWOTH) ? "w" : "-");
            printf((statinfo.st_mode & S_IXOTH) ? "x " : "- ");
            printf("%ld ", statinfo.st_nlink);
            passwd_t *pwd = getpwuid(statinfo.st_uid);
            group_t *grp = getgrgid(statinfo.st_gid);

            if (pwd->pw_name) {
                printf("%s ", pwd->pw_name);
            } else {

                printf("%d ", statinfo.st_uid);
            }
            if (grp->gr_name) {
                printf("%s ", grp->gr_name);
            } else {
                printf("%d ", statinfo.st_gid);
            }
            printf("%ld ", statinfo.st_size);
            char str[36];
            printf("%s", formatdate(str, statinfo.st_mtime));
        }
        if (!is_chr_in_str(flags, 'l')) {
            printf("%c ", get_file_type(statinfo.st_mode));
        } else {
            printf(" ");
        }

        printf("%s\n", dirinfo->d_name);
    }
    if (errno) {
        perror("readdir");
    }

    if (is_chr_in_str(flags, 'l')) {
        printf("total %u\n", total_blocks / 2);
    }
    // <-
}

// helpful functions
char get_file_type(mode_t type) {
    return S_ISSOCK(type) ? 's' : S_ISDIR(type) ? 'd' : S_ISLNK(type) ? 'l' : S_ISREG(type) ? '-' : S_ISBLK(type) ? 'b' : S_ISCHR(type) ? 'c' : S_ISFIFO(type) ? 'p' : '?';
}

char *formatdate(char *str, time_t val) {
    time_t time_now;
    time(&time_now);
    if (difftime(time_now, val) > 15778463) {
        strftime(str, 36, "%b %d %Y", localtime(&val));
    } else {
        strftime(str, 36, "%b %d %H:%M", localtime(&val));
    }

    return str;
}

int is_chr_in_str(char *flags, char wanted) {
    return strchr(flags, wanted) != NULL;
}