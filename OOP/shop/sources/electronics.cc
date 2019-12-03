#include "../headers/electronics.hh"

Electronics::Electronics(){
    type = "";
    warranty_date = NULL;
    warranty_conditions = "";
}

Electronics::Electronics(string type, int warranty_date, string warranty_conditions){
    this->type = type;
    this->warranty_date = warranty_date;
    this->warranty_conditions = warranty_conditions;
};