#ifndef AIRPORT_HH
#define AIRPORT_HH
#include "string"
#include "base.hh"
#include "vector"
using std::string;
using std::vector;

class BasePlane;

class Airport{
    public:
        int maxSize;
        int maxPlanes;
        int accepts_millitary; // army or not ()
        int accepts_public;
        vector<BasePlane> planes_now;
        int positionX;
};

#endif // !AIRPORT_HH