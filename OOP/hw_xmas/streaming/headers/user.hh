#ifndef USER_HH
#define USER_HH
#include "string"
#include "vector"
#include "payment.hh"
using std::string;
using std::vector;

class Payment;

class User{
    protected:
        string user_name;
        string user_email;
        vector<Payment> payments;

    public:
        User();

        User(string, string, vector<Payment>);

    string getUserName();
    string getUserEmail();
    vector<Payment> getPayments();
};

#endif