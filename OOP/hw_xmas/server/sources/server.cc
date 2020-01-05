#include "../headers/server.hh"

Server::Server(vector<string> paths, map<string, Object> objects) 
    : paths(paths),
      objects(objects) {};

Response* Server::routeRequest(Request* req){
    for (int i = 0; i < this->paths.size(); ++i){
        if (req->getWantedPath == this->paths[i]){
            return objects[this->paths[i]].handleRequest(req);
        }
    }
}