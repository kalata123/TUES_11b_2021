#include "../headers/service.hh"

Service::Service(vector<Media*> media_offstringered, vector<User> users) 
    : media_offered(media_offered),
      users(users) {};

vector<Media*> Service::getMediaOffered(){
    return this->media_offered;
}

Payment Service::getPaymentByUser(User user){
    int size = this->users.size();
    for (int i = 0; i < size; ++i){
        if (user.getUserName() == this->users[i].getUserName())
            return this->users[i].getPayments()[0];
    }
}

void Service::markPaymentAsPaid(User user, int index){
    int size = this->users.size();
    for (int i = 0; i < size; ++i){
        if (user.getUserName() == this->users[i].getUserName())
            this->users[i].getPayments()[index].setAsPaid();
    }
}

auto Service::getMediaByTitle(string title){
    int size = this->media_offered.size();
    for (int i = 0; i < size; ++i){
        if (title == this->media_offered[i]->getTitle()) {
            return this->media_offered[i];
        }
    }
}

void Service::addNewMedia(Media* media){
    this->media_offered.push_back(media);
}

void Service::addNewUser(User user){
    this->users.push_back(user);
}