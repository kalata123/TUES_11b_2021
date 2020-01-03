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

        string getTitle();
        string getAuthor();
        virtual unsigned int getPrice();
        void raiseErrorNoSuchMedia();
};

#endif