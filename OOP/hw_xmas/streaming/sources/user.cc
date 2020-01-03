#include "../headers/user.hh"

User::User(string user_name, string user_email, vector<Payment> payments)
    : user_email(user_email),
      user_name(user_name),
      payments(payments) {};

string User::getUserName(){
    return this->user_name;
}

string User::getUserEmail(){
    return this->user_email;
}

vector<Payment> User::getPayments(){
    return this->payments;
}