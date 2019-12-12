#ifndef CAR_HH
#define CAR_HH
#include "string"
using std::string;

#include "baseVehicles.hh"

class Car : public BaseVehicles{
    private:
        string fuelType;        
    public:
        Car(){};
        Car(string model, string ramaNum, string fuelType);
        string get_fuelType();
        string get_model();
        string get_ramaNum();
};

#endif