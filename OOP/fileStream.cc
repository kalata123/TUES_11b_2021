#include "iostream"
#include "fstream"
#include "string"
using namespace std;

int main(int argc, char const *argv[])
{
    ofstream out;
    out.open("test.txt");
    string name;

    cout << "Enter your name: ";
    getline(cin, name);
    out << name << endl;

    int age;
    cout << "Enter your age: ";
    cin >> age;
    out << age << endl;

    out.close();

    ifstream in;

    in.open("test.txt");

    string ifName;
    getline(in, ifName);
    cout << ifName << endl;

    int age2;
    in >> age2;
    cout << age2<< endl;
    return 0;
}