#ifndef OTHERS_HH
#define OTHERS_HH
#include "string"
#include "base.hh"
using std::string;

class Others : public Base{
    public:
        Others(){}
        Others(string, string, double, string, string){}
        string info;
};


#endif // !OTHERS_HH