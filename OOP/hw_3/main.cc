#include <iostream>
using namespace std;

#include "headers/shop.hh"

int main(){
    vector<User> users;
    vector<Product *> products;
    vector<Order> orders;
    Shop shop = Shop(users, products, orders);

    return 0;
}