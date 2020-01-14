#ifndef HUMAN_HH
#define HUMAN_HH
#include "string"
using std::string;
#include "Character.hh"

class Human : public Character{
    protected:
    public:
        Human();

        Human(string name) : Character(name, 0, 10) {};
};

#endif