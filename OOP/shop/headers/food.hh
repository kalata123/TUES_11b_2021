#ifndef FOOD_HH
#define FOOD_HH
#include "string"
using std::string;

class Food {
    public:
    Food(){}
    Food(string, int, string, bool){}
        string type;
        int exp_date;
        string alergies;
        bool is_bds;
};


#endif // !FOOD_HH