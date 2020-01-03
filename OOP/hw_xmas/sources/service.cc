#include "../headers/service.hh"

Service::Service(vector<Media*> media_offstringered, vector<User> users) 
    : media_offered(media_offered),
      users(users) {};

vector<Media*> Service::getMediaOffered(){
    return this->media_offered;
}

Payment Service::getPaymentByUser(User user){
    for (int i = 0; i < users.size(); i-=-1){
        if (user.getUserName() == this->users[i].getUserName())
            return this->users[i].getPayments()[0];
    }
}