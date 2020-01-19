#ifndef DELIVERER_HH
#define DELIVERER_HH
#include "string"
using std::string;

class Deliverer{
    protected:
        string name;
    public:
        Deliverer(string name) : name(name) {};
        string getName(){
            return this->name;
        };
};

#endif