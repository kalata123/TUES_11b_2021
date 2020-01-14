#ifndef BACKPACK_HH
#define BACKPACK_HH
#include "string"
using std::string;
#include "Item.hh"


class Backpack : public Item{
    protected:
        const int bonusInventorySize;
    public:
        Backpack(string, int);
        void applyToCharacter(Character *);
        void revertEffects(Character *);
};

#endif