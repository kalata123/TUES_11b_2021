#ifndef BOOK_HH
#define BOOK_HH
#include "string"
#include "media.hh"
using std::string;

class Book : public Media{
    public:
        Book(string, string, unsigned int);

        unsigned int getPrice();
};

#endif