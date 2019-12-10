#ifndef LOADPLANE_HH
#define LOADPLANE_HH
#include "string"
#include "base.hh"
using std::string;

class LoadPlane : public BasePlane{
    public:
        int passangers;
        int exits;
        int seats;
        LoadPlane();
        LoadPlane(int passangers, int exits, int seats);
};

#endif // !LOADPLANE_HH