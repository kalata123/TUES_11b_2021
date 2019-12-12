#include "parts.hh"

Parts::Parts(string name, string vehicle, int price) 
    : name (name), vehicle (vehicle), price (price){};


int Parts::get_price(){
    return this->price;
}