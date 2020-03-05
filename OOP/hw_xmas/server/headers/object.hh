#ifndef OBJECT_HH
#define OBJECT_HH
#include "string"
#include "vector"
#include "response.hh"
#include "request.hh"
using std::string;
using std::vector;

class Response;
class Request;

class Object{
    protected:
        vector<string> users;
    public:
        Object(){};

        Object(/*some params*/);

        Response* handleRequest(Request* req);

        vector<string> getUsers();
};

#endif