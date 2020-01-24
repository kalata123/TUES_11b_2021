#ifndef ORDER_HH
#define ORDER_HH
#include "string"
#include "user.hh"
#include "product.hh"
#include "vector"
#include "map"
using std::string;
using std::vector;
using std::map;

class User;
class Product;

class Order{
    protected:
        int id;
        User user;
        vector<Product *> ordered_products; 
        map<string, int> capacity_for_each_type; // type - capacity
        int status = 0; // 0 - new/ 1 - Accepted/ 2 - Sent
    public:
        Order(int, User, vector<Product *>, map<string, int>);
        int getId();
        User getUser();
        vector<Product *> getOrderedTypes();
        map<string, int> getCapacityForEachType();
        int getStatus();

        void addToOrder(Product *);
        void setStatus(int);
};

#endif