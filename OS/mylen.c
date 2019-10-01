#include <stdio.h>
//------------------------------------------------------------------------
// NAME: Kaloyan Angelov
// CLASS: XIb
// NUMBER: 15
// PROBLEM: #1
// FILE NAME: mylen.c
// FILE PURPOSE: implementing strlen
//------------------------------------------------------------------------

int mylen(char* a){
    //------------------------------------------------------------------------
    // FUNCTION: mylen
    // returns lenght of a
    // PARAMETERS: char *a - array
    //------------------------------------------------------------------------
    int i = 0;
    while(a[i] != '\0') i++;
    return i;
}