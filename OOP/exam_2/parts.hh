#ifndef PARTS_HH
#define PARTS_HH
#include "string"
using std::string;

class Parts{
    private:
        string name;
        int price;
        string vehicle; // car or motor
    public:
        Parts(){};
        Parts(string name, string vehicle, int price);
        int get_price();
};

#endif