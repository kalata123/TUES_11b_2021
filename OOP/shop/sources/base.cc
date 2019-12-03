#include "../headers/base.hh"

Base::Base(){
    name = "";
    manufacturer = "";
    price = NULL;
    barcode = "";
    description = "";
};

Base::Base(string name, string manufacturer, double price, string barcode, string description){
    this->name = name;
    this->manufacturer = manufacturer;
    this->price = price;
    this->barcode = barcode;
    this->description = description;
};