#include "clients.hh"

Clients::Clients(string name, string email) : name(name), email(email){}

string Clients::get_name(){
    return this->name;
}

string Clients::get_email(){
    return this->email;
}