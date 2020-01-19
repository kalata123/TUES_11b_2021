#include "../headers/user.hh"

User::User(int id, string username, string password)
: id(id), username(username), password(password) {}

int User::getId(){
    return this->id;
}

string User::getUsername(){
    return this->username;
};

string User::getPassword(){
    return this->password;
};