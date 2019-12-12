#ifndef SERVIZ_HH
#define SERVIZ_HH
#include "vector"
#include "car.hh"
#include "clients.hh"
#include "order.hh"
#include "motor.hh"
using std::vector;

class Serviz{
    private:
        vector<Clients> clients;
        vector<Car> cars; // since motors can't enter the Serviz
        vector<Order> orders;
    public:
        class NoMotors {};
        class FullServiz {};
        class NoSuchClient {};
        class NoSuchCar {};
        class NoSuchOrder {};

        Serviz(){};
        Serviz(vector<Clients> clients, vector<Car> cars, vector<Order> orders);
        void add_car(Car car);
        void add_motor(Motor motor); // simply will throw
        vector<Order> get_orders_for_client(Clients client);
        vector<Order> get_orders_for_cars(Car car);
        vector<Order> get_orders_for_motors(Motor car); // simply will throw
        Order get_order_by_number(string number);
};

#endif