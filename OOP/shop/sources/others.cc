#include "../headers/others.hh"

Others::Others(){
    name = "";
    manufacturer = "";
    price = NULL;
    barcode = "";
    description = "";
}

Others::Others(string name, string manufacturer, double price, string barcode, string description){
    this->name = name;
    this->manufacturer = manufacturer;
    this->price = price;
    this->barcode = barcode;
    this->description = description;
};