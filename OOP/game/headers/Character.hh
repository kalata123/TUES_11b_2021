#ifndef CHARACTER_HH
#define CHARACTER_HH
#include "string"
using std::string;
#include "vector"
using std::vector;

#include "Item.hh"

class Item;

class Character{
    protected:
        string name;
        int attack;
        int defence;
        int inventorySize;
        vector<Item *> inventory; // could be map<>
        bool alive;
    public:
        Character();
        Character(string, int, int);

        string getName();
        int getAttack();
        int getDefence();
        int getInventorySize();
        void setAttack(int);
        void setDefence(int);
        void setInventorySize(int);
        void attackCharacter(Character *);
        void acquireItem(Item *);
        void dropItem(int );
        void useItem(int slot);
        void die();
};

#endif