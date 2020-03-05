#include "headers/product.hh"

Product::Product(string name, double price, int quantity, Deliverer deliverer, int delivery_days)
: name(name), price(price), quantity(quantity), deliverer(deliverer), delivery_days(delivery_days) {};


string Product::getName(){
    return this->name;
};

double Product::getPrice(){
    return this->price;
};

int Product::getQuantity(){
    return this->quantity;
};

Deliverer Product::getDeliverer(){
    return this->deliverer;
};

int Product::getDeliveryDays(){
    return this->delivery_days;
};
