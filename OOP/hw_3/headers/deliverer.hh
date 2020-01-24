#ifndef DELIVERER_HH
#define DELIVERER_HH
#include "string"
using std::string;

class Deliverer{
    protected:
        string name;
        int id;
    public:
        Deliverer(string name, int id) : name(name), id(id) {};
        string getName(){
            return this->name;
        };
        int getId(){
            return this->id;
        }
};

#endif