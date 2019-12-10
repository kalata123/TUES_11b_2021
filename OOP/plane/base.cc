#include "base.hh"


BasePlane::BasePlane(){
    int size = NULL;
    int flightNumber = NULL;
    int type = NULL;
    int speed = NULL;
    int fuel = NULL;
    int expencePerKM = NULL;
    int positionX = NULL;
}


ostream & operator<<(ostream& os, BasePlane& bp){
    os << bp.size << bp.flightNumber << bp.type << bp.speed 
       << bp.fuel << bp.expencePerKM << bp.positionX << std::endl;
}