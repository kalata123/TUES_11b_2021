#include "headers/order.hh"

Order::Order(
    int id,
    User user,
    vector<Product *> ordered_products,
    map<string, int> capacity_for_each_type)
    :   id(id),
        user(user),
        ordered_products(ordered_products),
        capacity_for_each_type(capacity_for_each_type),
        status(0) {};


int Order::getId(){
    return this->id;
}

User Order::getUser(){
    return this->user;
}

vector<Product *> Order::getOrderedTypes(){
    return this->ordered_products;
}

map<string, int> Order::getCapacityForEachType(){
    return this->capacity_for_each_type;
}

int Order::getStatus(){
    return this->status;
}

void Order::addToOrder(Product * new_product){
    for (int i = 0; i < this->ordered_products.size(); ++i){
        if (new_product->getName() == this->ordered_products[i]->getName()){
            this->capacity_for_each_type[new_product->getName()] += 1;
            return;
        }
    }
    this->capacity_for_each_type[new_product->getName()] = 1;
    this->ordered_products.push_back(new_product);
}

void Order::setStatus(int new_status){
    if (this->status == new_status) return;
    this->status = new_status;
}