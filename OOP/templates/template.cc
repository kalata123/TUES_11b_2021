#include <iostream>
#include "string"
using namespace std;

template<class T>
T Max(T a, T b){
    return a > b ? a: b;
}

int main(){
    int a = 4, b = 6;
    double c = 5.2, d = 5.6;
    string e = "Hello", f = "World";
    cout << Max(a, b) << endl;
    cout << Max(c, d) << endl;
    cout << Max(e, f) << endl;
    return 0;
}
