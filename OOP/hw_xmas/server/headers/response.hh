#ifndef RESPONSE_HH
#define RESPONSE_HH
#include "string"
#include "vector"
using std::string;
using std::vector;

class Response{
    protected:
        string message;
        int status;
        vector<string> users;
    public:
        Response(){};

        Response(string, int);

        Response(string, int, vector<string>);
};

#endif