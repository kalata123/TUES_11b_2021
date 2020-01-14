#include "../headers/Backpack.hh"

Backpack::Backpack(string name, int bonusInventorySize) 
: Item(name), bonusInventorySize(bonusInventorySize) {};


void Backpack::applyToCharacter(Character * character){
    character->setInventorySize(character->getInventorySize() + bonusInventorySize);
}
void Backpack::revertEffects(Character * character){
    character->setInventorySize(character->getInventorySize() - bonusInventorySize);
}
