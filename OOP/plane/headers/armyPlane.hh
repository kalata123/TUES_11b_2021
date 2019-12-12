#ifndef ARMYPLANE_HH
#define ARMYPLANE_HH
#include "string"
#include "base.hh"
using std::string;

class ArmyPlane : public BasePlane{
    public:
        int force;
        ArmyPlane(int size, int flightNumber, int type, 
                  int speed, int fuel, int expencePerKM,
                  int positionX, int force);
};

#endif // !ARMYPLANE_HH