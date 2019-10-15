#include "iostream"
#include "sstream"
#include "string"
using namespace std;

int main(int argc, char const *argv[])
{
    string data = "3.14 2ke";
    istringstream in(data);

    double pi;
    in >> pi;
    if (in){
        cout << "nice" << endl << "pi: " << pi << endl;
    }else{
        cout << "Nok" << endl;
    }

    int num;
    in >> num;
    if (in){
        cout << "nice" << endl << "num: " << num << endl;
    }else {
        cout << "fked" << endl;
    }

    in.clear(); // deletes the failing bit at the end and the rest of the data becomes readable

    string n = "not set";
    in >> n;
    if (in){
        cout << "nice" << endl << "string: " << n << endl;
    }else {
        cout << "bad" << endl;
    }

    if(in.eof()){
        cout << "Reached EOF" << endl;
    }

    return 0;
}