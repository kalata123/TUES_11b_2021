#include "../headers/Potion.hh"

Potion::Potion(string name, int bonusAttack, int bonusArmor) 
: Item(name), bonusAttack(bonusAttack), bonusArmor(bonusArmor) {};


void Potion::applyToCharacter(Character * character){
    character->setDefence(character->getDefence() + bonusArmor);
    character->setAttack(character->getAttack() + bonusArmor);
}