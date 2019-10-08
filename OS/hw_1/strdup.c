#include <stdlib.h>
#include <string.h>
char* strdup(const char* str){
    char* s = (char*)malloc(sizeof(char)*strlen(str));
    strcpy(s,str);
    return s;
}
