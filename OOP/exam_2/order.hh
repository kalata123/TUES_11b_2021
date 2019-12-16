#ifndef ORDER_HH
#define ORDER_HH
#include "uslugi.hh"
#include "parts.hh"
#include "clients.hh"
#include "string"
#include "vector"
#include "car.hh"
using std::string;

class Order{
    private:
        Clients client;
        Car car;
        Uslugi usluga;
        vector<Parts> parts;
        int ord_count = 0;
        int finalPrice;
        string number;
        string vehicle;
        string status;
    public:
        Order(){};

        Order(string number, Clients client, Uslugi usluga, vector<Parts> parts, string vehicle, int finalPrice, string status);
        string get_cl_name();
        string get_cl_email();
        string get_car_model();
        string get_car_ramaNum();
        string get_car_fuelType();

};

#endif
