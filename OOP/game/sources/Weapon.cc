#include "../headers/Weapon.hh"

Weapon::Weapon(string name, int bonusAttack) : Item(name), bonusAttack(bonusAttack){};

void Weapon::applyToCharacter(Character * character) {
    character->setAttack(character->getAttack() + this->bonusAttack);
}

void Weapon::revertEffects(Character * character){
    character->setAttack(character->getAttack() - this->bonusAttack);
}