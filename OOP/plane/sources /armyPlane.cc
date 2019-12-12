#include "../headers/armyPlane.hh"

ArmyPlane::ArmyPlane(
    int size, 
    int flightNumber, 
    int type, 
    int speed, 
    int fuel, 
    int expencePerKM,
    int positionX, 
    int force)
  :
    BasePlane(
        size,
        flightNumber,
        type,
        speed,
        fuel,
        expencePerKM,
        positionX),
    force(force) {}