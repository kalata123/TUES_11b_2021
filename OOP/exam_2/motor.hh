#ifndef MOTOR_HH
#define MOTOR_HH

#include "baseVehicles.hh"

class Motor : public BaseVehicles{
    private:
        int kubatura;        
    public:
        Motor(){};

        Motor(string model, string ramaNum, int kubatura);
};

#endif