#include "../headers/loadPlane.hh"

LoadPlane::LoadPlane(
    int size, 
    int flightNumber, 
    int type, 
    int speed, 
    int fuel, 
    int expencePerKM,
    int positionX, 
    int loadNow,
    int maxLoad)
  :
    BasePlane(
        size,
        flightNumber,
        type,
        speed,
        fuel,
        expencePerKM,
        positionX),
    loadNow(loadNow),
    maxLoad(maxLoad) {}