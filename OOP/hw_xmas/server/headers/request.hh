#ifndef REQUEST_HH
#define REQUEST_HH
#include "string"
using std::string;

class Request{
    protected:
        string sender_ip_addr;
        string wanted_path;
        string username;
        string password;
    public:
        Request(){};

        Request(string, string);

        Request(string, string, string, string);

        string getSenderIdAddr();
        string getWantedPath();
        string getUserName();
        string getPassword();

};

#endif