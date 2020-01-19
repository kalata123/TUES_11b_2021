#ifndef PRODUCT_HH
#define PRODUCT_HH
#include "string"
#include "deliverer.hh"
using std::string;

class Deliverer;

class Product{
    protected:
        string name;
        double price;
        int quantity;
        Deliverer deliverer;
        int delivery_days;
    public:
        Product(string, double, int, Deliverer, int);

        string getName();
        double getPrice();
        int getQuantity();
        Deliverer getDeliverer();
        int getDeliveryDays();

};

#endif