#include "../headers/payment.hh"
#include "string"

Payment::Payment(
    unsigned int start_year,
    unsigned int start_month,
    unsigned int start_day,
    unsigned int end_year,
    unsigned int end_month,
    unsigned int end_day,
    vector<Media*> used_media,
    unsigned int price_to_pay,
    bool is_paid) 
    :
    used_media(used_media),
    price_to_pay(price_to_pay),
    is_paid(is_paid) {
        this->begin_date.year = start_year;
        this->begin_date.month = start_month;
        this->begin_date.day = start_day;

        this->end_date.year = end_year;
        this->end_date.month = end_month;
        this->end_date.day = end_day;
    };


unsigned int Payment::getPriceToPay(){
    return this->price_to_pay;
}

string Payment::getBeginDate(){
    return std::to_string(this->begin_date.day) + "." +
           std::to_string(this->begin_date.month) + "." +
           std::to_string(this->begin_date.year);
}

string Payment::getEndDate(){
    return std::to_string(this->end_date.day) + "." +
           std::to_string(this->end_date.month) + "." +
           std::to_string(this->end_date.year);
}

vector<Media*> Payment::getUsedMedia(){
    return this->used_media;
}

bool Payment::getIsPaid(){
    return this->is_paid;
}

void Payment::setAsPaid(){
    this->is_paid = true;
}