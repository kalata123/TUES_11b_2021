#include "headers/tech.hh"

Tech::Tech(
    string name,
    double price,
    int quantity,
    Deliverer deliverer,
    int delivery_days,
    string type,
    int warranty_years,
    int weight) 
    :   Product(name, price, quantity, deliverer, delivery_days), 
        type(type), 
        warranty_years(warranty_years), 
        weight(weight) {};

string Tech::getType(){
    return this->type;
};
int Tech::getWarrantyYears(){
    return this->warranty_years;
};
int Tech::getWeight(){
    return this->weight;
};