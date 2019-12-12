#ifndef USLUGI_HH
#define USLUGI_HH
#include "string"
#include "vector"
using std::string;
using std::vector;

#include "parts.hh"

class Uslugi : public Parts{
    private:
        string name;
        vector<Parts> parts;
        int price;
        string vehicle;
    public:
        Uslugi(){};

        Uslugi(string name, vector<Parts> parts, int price, string vehicle);
        int get_price();
};

#endif