#ifndef BASE_HH
#define BASE_HH
#include "ostream"
#include "string"
using std::string;
using std::ostream;

class BasePlane{
    public:
        int size;
        int flightNumber;
        int type; // army or not ()
        int speed;
        int fuel;
        int expencePerKM;
        int positionX;
        BasePlane();
        BasePlane(int size, int flightNumber, bool type,
                  int speed, int fuel, int expencePerKM, 
                  int positionX);
};

ostream & operator<<(ostream& os, BasePlane& bp);


#endif // !BASE_HH