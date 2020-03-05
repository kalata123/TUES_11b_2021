#ifndef SHOP_HH
#define SHOP_HH
#include "string"
#include "user.hh"
#include "product.hh"
#include "deliverer.hh"
#include "vector"
#include "order.hh"
using std::string;
using std::vector;
using std::pair;
using std::exception;

class User;
class Product;
class Order;

class Shop{
    protected:
        vector<User> users;
        vector<Product *> products;
        vector<Order> orders;
    public:
        Shop(Shop const&);
        Shop(vector<User>, vector<Product *>, vector<Order>);

        class ErrorExistingUser: exception {};
        class ErrorExistingOrder: exception {};
        class ErrorInOrder: exception {};

        void addUser(User * user);
        void add_product(Product * product);
        void create_order(Order * order);
        pair<double, int> accept_order(int order_id);
        void send_order(int order_id);
        vector<Order> get_orders_by_user(int user_id);
        vector<Product *> get_products_by_deliverer(int deliverer_id);

};

#endif