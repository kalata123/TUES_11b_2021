#include "iostream"
using namespace std;

class A{
    int a = 1;
    public:
        int b = 2;
    protected:
        int c = 3;
};

class B : public A{
    int d = 4;
    public:
        int e = 5;
    protected:
        int f = 6;
};

class B : protected A{
    int d = 4;
    public:
        int e = 5;
    protected:
        int f = 6;
};

int main(int argc, const char** argv) {
    A a;
    B b;
    
    cout << a.b << endl;
    //cout << b.b << endl;
    cout << b.e << endl;
    return 0;
}