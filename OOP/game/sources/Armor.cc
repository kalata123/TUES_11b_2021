#include "../headers/Armor.hh"

Armor::Armor(string name, int bonusArmor) 
: Item(name), bonusArmor(bonusArmor) {};

void Armor::applyToCharacter(Character * character){
    character->setDefence(character->getDefence() + bonusArmor);
}

void Armor::revertEffects(Character * character){
    character->setDefence(character->getDefence() - bonusArmor);
}