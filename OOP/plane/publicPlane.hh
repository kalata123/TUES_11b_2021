#ifndef PUBLICPLANE_HH
#define PUBLICPLANE_HH
#include "string"
#include "base.hh"
using std::string;

class PublicPlane : public BasePlane{
    public:
        int passangers;
        int exits;
        int seats;
        PublicPlane();
        PublicPlane(int passangers, int exits, int seats);
};

#endif // !PUBLICPLANE_HH