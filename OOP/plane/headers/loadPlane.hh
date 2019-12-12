#ifndef LOADPLANE_HH
#define LOADPLANE_HH
#include "string"
#include "base.hh"
using std::string;

class LoadPlane : public BasePlane{
    public:
        int loadNow;
        int maxLoad;
        LoadPlane(int size, int flightNumber, int type, 
                  int speed, int fuel, int expencePerKM,
                  int positionX, int loadNow, int maxLoad);
};

#endif // !LOADPLANE_HH