#ifndef BASE_HH
#define BASE_HH
#include "string"
using std::string;

class Base {
    public:
        Base(){}
        Base(string, string, double, string, string){}
        string name;
        string manufacturer;
        double price;
        string barcode;
        string description;
};


#endif // !BASE_HH