#ifndef ORK_HH
#define ORK_HH
#include "string"
using std::string;
#include "Character.hh"

class Ork : public Character{
    protected:
    public:
        Ork();

        Ork(string name) : Character(name, 10, 0) {};
};

#endif