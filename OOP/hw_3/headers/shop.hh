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

class User;
class Product;
class Order;

class Shop{
    protected:
        vector<User> users;
        vector<Product *> products;
        vector<Order> orders;
    public:
        Shop();
        pair<double, int> accept_order(int order_id);
        void send_order(int order_id);
        vector<Order const&> get_orders_by_user(int user_id) const;
        vector<Product *> get_products_by_deliverer(int deliverer_id);

};

#endif