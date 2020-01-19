#include "../headers/order.hh"

Order::Order(
    int id,
    User user,
    vector<Product *> oredered_types,
    map<string, int> capacity_for_each_type,
    int status)
    :   id(id),
        user(user),
        oredered_types(oredered_types),
        capacity_for_each_type(capacity_for_each_type),
        status(status) {};


int Order::getId(){
    return this->id;
};
User Order::getUser(){
    return this->user;
};
vector<Product *> Order::getOrderedTypes(){
    return this->oredered_types;
};
map<string, int> Order::getCapacityForEachType(){
    return this->capacity_for_each_type;
};
int Order::getStatus(){
    return this->status;
};
