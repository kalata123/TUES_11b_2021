#ifndef SERVICE_HH
#define SERVICE_HH
#include "string"
#include "user.hh"
#include "media.hh"
#include "vector"
#include "payment.hh"
using std::string;
using std::vector;

class Media;
class User;
class Payment;

class Service{
    protected:
        vector<Media*> media_offered;
        vector<User> users;
    public:
        Service();

        Service(vector<Media*>, vector<User>);

        void addNewUser(User);
        void addNewMedia(Media*);
        vector<User> getUsers();
        Payment getPaymentByUser(User);
        vector<Media*> getMediaOffered();
        void markPaymentAsPaid(User, int);
        auto getMediaByTitle(string);
};

#endif