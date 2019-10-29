#include "iostream"
#include "string"
using namespace std;



int main() {
    const int i = 4;

    // i = 3; // Error

    char str1[] = "Hello";

    char str2[] = "Alo";

    const char* p1 = str1;
    p1 = str2;
    // p1[2] = 'A'; // Error

    char* const p2 = str2;
    // p2 = str1; // Error
    p2[2] = 'A';

    const char* const p3 = str1;
    cout << p3 << endl;

    int a = 2;
    int& ra = a;
    cout << ra << endl;
    ra = 3;
    cout << a << endl;


    return 0;
}