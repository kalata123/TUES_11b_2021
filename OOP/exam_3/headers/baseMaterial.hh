#ifndef BASEMATERIAL_HH
#define BASEMATERIAL_HH
#include "string"
using std::string;

class BaseMaterial{
    protected:
        string name;
        string type;
        int quantity;
    public:
        BaseMaterial(string, string, int);

        string getName();
        string getType();
        int getQuantity();
};

#endif