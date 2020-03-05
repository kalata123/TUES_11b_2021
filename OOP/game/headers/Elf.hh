#ifndef ELF_HH
#define ELF_HH
#include "string"
using std::string;
#include "Character.hh"

class Elf : public Character{
    protected:
    public:
        Elf();

        Elf(string name) : Character(name, 5, 5) {};
};

#endif