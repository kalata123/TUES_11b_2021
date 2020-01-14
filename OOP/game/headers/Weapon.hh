#ifndef WEAPON_HH
#define WEAPON_HH
#include "string"
using std::string;
#include "Item.hh"

class Weapon : public Item{
    protected:
        const int bonusAttack;
    public:
        Weapon(string, int);
        void applyToCharacter(Character *);
        void revertEffects(Character *);

};

#endif