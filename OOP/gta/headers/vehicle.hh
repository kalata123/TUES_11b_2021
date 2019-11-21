#ifndef VEHICLE_HH
#define VEHICLE_HH
#include "entity.hh"
class Vehicle : public Entity {
    int sth;
    public:
        Vehicle();
        Vehicle(int sth);
};
#endif // !VEHICLE_HH