#ifndef USER_HH
#define USER_HH
#include "string"
using std::string;

class User{
    protected:
        int id;
        string username;
        string password;
    public:
        User(int id, string username, string password);
        int getId();
        string getUsername();
        string getPassword();
};

#endif