#include "headers/shop.hh"

Shop::Shop(Shop const& shop) 
: users(shop.users), products(shop.products), orders(shop.orders) {};

Shop::Shop(vector<User> users, vector<Product *> products, vector<Order> orders)
: users(users), products(products), orders(orders){};

void Shop::addUser(User * user){
    for (int i = 0; i < this->users.size(); ++i){
        if (this->users[i].getUsername() == user->getUsername()) throw ErrorExistingUser();
    }
    this->users.push_back(*user);
}

void Shop::add_product(Product * product){
    for (int i = 0; i < this->products.size(); ++i){
        if (this->products[i]->getName() == product->getName()) return;
    }
    this->products.push_back(product);
}

void Shop::create_order(Order * order){
    for (int i = 0; i < this->orders.size(); ++i){
        if (this->orders[i].getId() == order->getId()) throw ErrorExistingOrder();
    }

    bool in_users = false;
    for (int i = 0; i < this->users.size(); ++i){
        if (this->users[i].getId() == order->getUser().getId()) {
            in_users = true;
            break;    
        };
    }
    if (!in_users) throw ErrorExistingUser();

    vector<Product *> prods = order->getOrderedTypes();
    for (int i = 0; i < products.size(); ++i){
        for (int j = 0; j < prods.size(); ++j) {
            if (products[i]->getName() == prods[j]->getName() &&
                products[i]->getQuantity() < prods[j]->getQuantity()) {
                throw ErrorInOrder();
            }
        }
    }

    this->orders.push_back(*order);
}

pair<double, int> Shop::accept_order(int order_id){
    for (int i = 0; i < this->orders.size(); ++i){
        if (this->orders[i].getId() == order_id) {
            if (this->orders[i].getStatus() != 0) throw ErrorInOrder();
            this->orders[i].setStatus(1); // Status: Accepted Order
            vector< Product *> prods = this->orders[i].getOrderedTypes();
            map<string, int> mapped = this->orders[i].getCapacityForEachType();
            double final_price = 0;
            int days_before_arival = 0;
            for (int j = 0; j < prods.size(); ++i){
                final_price += mapped[prods[i]->getName()] * prods[i]->getPrice();
                days_before_arival += prods[i]->getDeliveryDays();
            }
            pair<double, int> paired = std::make_pair(final_price, days_before_arival);
            return paired;
        };
    }
    throw ErrorInOrder();
}

void Shop::send_order(int order_id){
    for (int i = 0; i < this->orders.size(); ++i){
        if (this->orders[i].getId() == order_id) {
            if (this->orders[i].getStatus() != 1) return;
            this->orders[i].setStatus(2); // Status: Sent Order
            return;
        }
    }

    throw ErrorInOrder();
}

vector<Order> Shop::get_orders_by_user(int user_id) {
    vector<Order> ords;
    bool in_users = false;
    for (int i = 0; i < this->orders.size(); ++i){
        if (this->orders[i].getUser().getId() == user_id){
            in_users = true;
            ords.push_back(this->orders[i]);
        }
    }
    if (!in_users) throw ErrorExistingUser();

    return ords;
}

vector<Product *> Shop::get_products_by_deliverer(int deliverer_id){
    vector<Product *> prods;
    for (int i = 0; i < this->products.size(); ++i){
        if (this->products[i]->getDeliverer().getId() == deliverer_id) {
            prods.push_back(this->products[i]);
        }
    }

    return prods;
}