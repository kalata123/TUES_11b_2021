#include "../headers/Item.hh"

Item::Item(string name)
: name(name){};

string Item::getName(){
    return this->name;
}