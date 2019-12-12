#include "../headers/base.hh"


BasePlane::BasePlane(){
    int size = NULL;
    int flightNumber = NULL;
    int type = NULL;
    int speed = NULL;
    int fuel = NULL;
    int expencePerKM = NULL;
    int positionX = NULL;
}

BasePlane::BasePlane(
    int size, int flightNumber, bool type,
    int speed, int fuel, int expencePerKM, 
    int positionX)
  :
    size(size),
    flightNumber(flightNumber),
    type(type),
    speed(speed),
    fuel(fuel),
    expencePerKM(expencePerKM),
    positionX(positionX){}

ostream & operator<<(ostream& os, BasePlane& bp){
    os << bp.size << bp.flightNumber << bp.type << bp.speed 
       << bp.fuel << bp.expencePerKM << bp.positionX << std::endl;
}