#ifndef ARMOR_HH
#define ARMOR_HH
#include "string"
using std::string;
#include "Item.hh"

class Armor : public Item{
    protected:
        const int bonusArmor;
    public:
        Armor(string, int);
        void applyToCharacter(Character *);
        void revertEffects(Character *);

};

#endif