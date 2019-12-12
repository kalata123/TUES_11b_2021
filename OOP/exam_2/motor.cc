#include "motor.hh"

Motor::Motor(string model, string ramaNum, int kubatura) 
    : BaseVehicles(model, ramaNum), kubatura(kubatura) {};