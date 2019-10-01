#include <iostream>

using namespace std;

class DivisionByZero {};
class TerminateException {};

double division(double a, double b){
    return b == 0 ? throw DivisionByZero() : a == 6798 ? throw TerminateException() : a/b;
}




int main() {
    double a, b;

    while (1)
    {
        cout << "Value a: ";
        cin >> a;
        cout << "Value b: ";
        cin >> b;
        try {
            cout << division(a, b) << endl;
        } catch (TerminateException) {
            cout << "Terminating" << endl;
            return -1;
        } catch (DivisionByZero){
            cout << "DivisionByZero" << endl;
        } 
    }
    
    return 0;
}
