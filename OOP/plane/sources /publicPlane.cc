#include "../headers/publicPlane.hh"

PublicPlane::PublicPlane(
    int size, int flightNumber, bool type,
    int speed, int fuel, int expencePerKM, 
    int positionX, int passangers, int exits, int seats)
  :
    BasePlane(
        size,
        flightNumber,
        type,
        speed,
        fuel,
        expencePerKM,
        positionX),
    passangers(passangers),
    exits(exits),
    seats(seats) {}