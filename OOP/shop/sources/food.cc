#include "../headers/food.hh"

Food::Food(){
    type = "";
    exp_date = NULL;
    alergies = "";
    is_bds = false;
}

Food::Food(string type, int exp_date, string alergies, bool is_bds){
    this->type = type;
    this->exp_date = exp_date;
    this->alergies = alergies;
    this->is_bds = is_bds;
}