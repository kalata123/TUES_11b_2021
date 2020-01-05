#include "../headers/response.hh"

Response::Response(string message, int status) 
    : message(message),
      status(status) {};

Response::Response(string message, int status, vector<string> users) 
    : message(message),
      status(status),
      users(users) {};