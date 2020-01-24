#include "headers/cloth.hh"

Cloth::Cloth(
    string name,
    double price,
    int quantity,
    Deliverer deliverer,
    int delivery_days,
    string color,
    int size,
    string material
    ) 
    :   Product(name, price, quantity, deliverer, delivery_days),
        color(color),
        size(size),
        material(material) {};


string Cloth::getColor(){
    return this->color;
};
int Cloth::getSize(){
    return this->size;
};
string Cloth::getMaterial(){
    return this->material;
};
