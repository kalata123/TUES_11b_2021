#include "baseVehicles.hh"

BaseVehicles::BaseVehicles(string model, string ramaNum) 
    : model(model), ramaNum(ramaNum) {};


string BaseVehicles::get_my_model(){
    return model;
}

string BaseVehicles::get_my_ramaNum(){
    return ramaNum;
}