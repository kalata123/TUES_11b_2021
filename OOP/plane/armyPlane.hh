#ifndef ARMYPLANE_HH
#define ARMYPLANE_HH
#include "string"
#include "base.hh"
using std::string;

class ArmyPlane : public BasePlane{
    public:
        int force;
        ArmyPlane();
        ArmyPlane(int passangers, int exits, int seats);
};

#endif // !ARMYPLANE_HH