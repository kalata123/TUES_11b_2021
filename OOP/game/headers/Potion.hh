#ifndef POTION_HH
#define POTION_HH
#include "string"
using std::string;
#include "Item.hh"

class Potion : public Item{
    protected:
        const int bonusAttack; 
        const int bonusArmor; 
    public:
        Potion(string, int, int);
        void applyToCharacter(Character *);
        void revertEffects(Character *);

};

#endif