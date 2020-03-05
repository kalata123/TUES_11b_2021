#ifndef PAYMENT_HH
#define PAYMENT_HH
#include "string"
#include "vector"
#include "media.hh"
using std::string;
using std::vector;

class Media;

typedef struct {
    unsigned int year;
    unsigned int month;
    unsigned int day;
} date_t;

class Payment{
    protected:
        date_t begin_date;
        date_t end_date;
        vector<Media*> used_media;
        unsigned int price_to_pay;
        bool is_paid;
    public:
        Payment();

        Payment(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, vector<Media*>, unsigned int, bool);

        unsigned int getPriceToPay();
        string getBeginDate();
        string getEndDate();
        vector<Media*> getUsedMedia();
        bool getIsPaid();
        void setAsPaid();
};

#endif