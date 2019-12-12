#ifndef ORDER_HH
#define ORDER_HH
#include "uslugi.hh"
#include "parts.hh"
#include "clients.hh"
#include "string"
#include "vector"
using std::string;

class Order{
    private:
        int ord_count = 0;
        string number;
        Clients client;
        Car car;
        Uslugi usluga;
        vector<Parts> parts;
        string vehicle;
        int finalPrice;
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