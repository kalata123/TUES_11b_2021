#ifndef BASEVEHICLES_HH
#define BASEVEHICLES_HH
#include "string"
using std::string;

class BaseVehicles{
    private:
        string model;
        string ramaNum;
    public:
        BaseVehicles(){};
        BaseVehicles(string model, string ramaNum);
        string get_my_model();
        string get_my_ramaNum();
};

#endif