#ifndef TECH_HH
#define TECH_HH
#include "string"
#include "product.hh"
using std::string;

class Tech: public Product{
    protected:
        string type;
        int warranty_years;
        int weight;
    public:
        Tech(string, double, int, Deliverer, int, string, int, int);
        string getType();
        int getWarrantyYears();
        int getWeight();
};

#endif