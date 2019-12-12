#include "order.hh"

Order::Order(string number, Clients client, Uslugi usluga, vector<Parts> parts, string vehicle, int finalPrice, string status) 
    :  client(client), usluga(usluga), parts(parts), vehicle(vehicle), status(status)
{
    int partsPrice;
    for (int i = 0; i < parts.size(); i++){
        partsPrice += parts[i].get_price();
    }
    finalPrice = usluga.get_price() + partsPrice;
    number = ord_count++;
};

string Order::get_cl_name(){
    return this->client.get_name();
}
string Order::get_cl_email(){
    return this->client.get_email();
}


string Order::get_car_model(){
    return this->car.get_model();
}
string Order::get_car_ramaNum(){
    return this->car.get_ramaNum();
}
string Order::get_car_fuelType(){
    return this->car.get_fuelType();
}