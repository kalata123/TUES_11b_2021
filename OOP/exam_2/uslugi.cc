#include "uslugi.hh"

Uslugi::Uslugi(string name, vector<Parts> parts, int price, string vehicle) 
            : name(name), parts(parts), price(price), vehicle(vehicle) {};


int Uslugi::get_price(){
    return this->price;
}