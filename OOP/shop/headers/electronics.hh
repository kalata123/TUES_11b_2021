#ifndef ELECTRONICS_HH
#define ELECTRONICS_HH
#include "string"
using std::string;

class Electronics {
    public:
    Electronics(){}
    Electronics(string, int, string){}
        string type;
        int warranty_date;
        string warranty_conditions;
};


#endif // !ELECTRONICS_HH