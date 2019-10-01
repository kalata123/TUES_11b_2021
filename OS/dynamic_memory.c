#include <stdio.h>
#include <string.h>

// byte - най-малката единица, която можем да адресираме, много често е 8 бита и се е приело за стандартно, но не винаги е 

// взимаме адресите с & и можем да го принтираме с {'%p'}

/* за достъпване на данните - трябва ни да знаем къде се намират и колко са големи 
(пр.) знаем къде се намира, но не знаем колко трябва да прочетем => ни трябват типове */

/*  Динамичната памет - <type> *p = malloc(<bytes>);
    sizeof(<type>)
    указателите (<type>*) са с еднаква големина и се определя спрямо архитектурата на процесора 2**(32|64 бита) 
*/

// HW:

// strlen - returns how big an array is
// strcat - copies one array into another
// swap - swaps 2 different variables
// void swap - swaps 2 differents types and swaps them
// strdup - ??

int mylen(char* a){
    int i = 0;
    while(a[i] != '\0') i++;
    return i;
}

void mycat(char *src, char *dest){
    int i = 0;
    while (src[i] != '\0'){ 
        dest[i] = src[i];
        i++;
    }
    // dest[i] = '\0';
}

int main() {
    char a[10];
    char b[11];
    gets(a);
    printf("%d\n", mylen(a));
    mycat(a, b);
    printf("1");
    for (int i = 0; i < 10; i++) printf("%c", b[i]);
    return 0;
}
