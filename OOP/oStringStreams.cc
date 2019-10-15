#include "iostream"
#include "sstream"
#include "string"
using namespace std;

int main(int argc, char const *argv[])
{
    ostringstream out;
    out << "Test " << "Is " << "Beyond " << "\n" << 123 << endl << "uuups" << endl;
    cout << out.str() << endl;
    
    return 0;
}