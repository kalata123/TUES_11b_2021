#include "../headers/Character.hh"

Character::Character(string name, int attack, int defence) 
: name(name), attack(attack), defence(defence), alive(true), inventorySize(1) {};

string Character::getName(){
    return this->name;
}

int Character::getAttack(){
    return this->attack;
}

int Character::getDefence(){
    return this->defence;
}

void Character::setAttack(int new_value){
    this->attack = new_value;
}

void Character::setDefence(int new_value){
    this->defence = new_value;
}

void Character::attackCharacter(Character * other){
    other->setDefence(other->getDefence() - this->attack);
    if (other->getDefence() < 0) die();
}

void Character::acquireItem(Item * item){
    if (this->inventory.size() < inventorySize) return;
    this->inventory.push_back(item);
}

void Character::dropItem(int slot){
    this->inventory[slot]->revertEffects(this);
    this->inventory.erase(this->inventory.begin() + slot);
}

void Character::die(){
    this->alive = false;
}

void Character::useItem(int slot){
    this->inventory[slot]->applyToCharacter(this);
}

void Character::setInventorySize(int new_size){
    this->inventorySize = new_size;
}

int Character::getInventorySize(){
    return this->inventorySize;
}