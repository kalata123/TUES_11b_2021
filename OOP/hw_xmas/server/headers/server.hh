#ifndef SERVER_HH
#define SERVER_HH
#include "string"
#include "vector"
#include "request.hh"
#include "map"
#include "object.hh"
using std::string;
using std::vector;
using std::map;

class Request;
class Object;

class Server{
    protected:
        vector<string> paths;
        map<string, Object> objects;
    public:
        Server(){};

        Server(vector<string>, map<string, Object>);

        Response* routeRequest(Request* req);

};

#endif