#ifndef MEDIA_HH
#define MEDIA_HH
#include "string"
using std::string;

class Media{
    protected:
        string title;
        string author;
        unsigned int price;
    public:
        Media();

        Media(string, string, unsigned int);

        // virtual int sumPrice();

        string getTitle();
        string getAuthor();
        virtual unsigned int getPrice();
};

#endif