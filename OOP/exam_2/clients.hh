#ifndef CLIENTS_HH
#define CLIENTS_HH
#include "string"
using std::string;

class Clients{
    private:
        string name;
        string email;
    public:
        Clients(){};

        Clients(string name, string email);
        string get_name();
        string get_email();
};

#endif