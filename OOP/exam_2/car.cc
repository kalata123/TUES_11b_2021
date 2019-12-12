#include "car.hh"

Car::Car(string model, string ramaNum, string fuelType) 
    : BaseVehicles(model, ramaNum), fuelType(fuelType) {};

string Car::get_fuelType(){
    return this->fuelType;
}
string Car::get_model(){
    return this->get_my_model();
}
string Car::get_ramaNum(){
    return this->get_my_ramaNum();
}