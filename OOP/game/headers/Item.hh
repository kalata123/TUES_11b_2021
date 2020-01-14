#ifndef ITEM_HH
#define ITEM_HH
#include "string"
using std::string;
#include "Character.hh"

class Character;

class Item{
    protected:
        string name;
    public:
        Item(string );

        string getName();
        virtual void applyToCharacter(Character *) = 0;
        virtual void revertEffects(Character *) = 0;
};

#endif