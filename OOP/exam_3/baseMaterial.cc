#include "headers/baseMaterial.hh"

BaseMaterial::BaseMaterial(string name, string type, int quantity) 
: name(name), type(type), quantity(quantity) {};


string BaseMaterial::getName(){
    return this->name;
}
string BaseMaterial::getType(){
    return this->type;
}
int BaseMaterial::getQuantity(){
    return this->quantity;
}