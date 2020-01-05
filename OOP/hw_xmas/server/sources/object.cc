#include "../headers/object.hh"
#include "vector"
using std::vector;


vector<string> Object::getUsers(){
    return this->users;
}

Response* Object::handleRequest(Request* req){
    switch (true)
    {
    case req->getWantedPath.find("login.html") != std::string::npos:
        return &Response("<html>login</html>", 200);
        break;

    case req->getWantedPath.find("home.html") != std::string::npos:
        return &Response("<html>home</html>", 200);
        break;

    case req->getWantedPath.find("login") != std::string::npos:
        for (auto i = 0; i < this->getUsers().size(); ++i)
            if (req->getUserName == this->getUsers()[i]){
                return &Response("OK", 200);
            }
        return &Response("Unauthorized", 403);
        break;
    
    case req->getWantedPath.find("get_users") != std::string::npos:
        for (auto i = 0; i < this->getUsers().size(); ++i)
            if (req->getUserName == this->getUsers()[i]){
                return &Response("OK", 200, this->getUsers());
            }
        break;
}