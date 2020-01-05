#include "../headers/request.hh"

Request::Request(string sender_ip_addr, string wanted_path)
    : sender_ip_addr(sender_ip_addr),
      wanted_path(wanted_path) {
        this->username = "";
        this->password = "";
      };

Request::Request(string sender_ip_addr, string wanted_path, string username, string password)
    : sender_ip_addr(sender_ip_addr),
      wanted_path(wanted_path),
      username(username),
      password(password) {};

string Request::getSenderIdAddr(){
    return sender_ip_addr;
}

string Request::getWantedPath(){
    return wanted_path;
}

string Request::getUserName(){
    if (username != ""){
        return username;
    }
}

string Request::getUserName(){
    if (password != ""){
        return password;
    }
}