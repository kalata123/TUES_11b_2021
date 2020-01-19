#ifndef CLOTH_HH
#define CLOTH_HH
#include "string"
#include "product.hh"
using std::string;

class Cloth: public Product{
    protected:
        string color;
        int size;
        string material;
    public:
        Cloth(string, double, int, Deliverer, int, string, int, string);
        string getColor();
        int getSize();
        string getMaterial();
};

#endif