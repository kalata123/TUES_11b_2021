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

        vector<Media*> getMediaOffered();
        Payment getPaymentByUser(User user);
        void markPaymentAsPaid();
        Media* getMediaByTitle();

};

#endif