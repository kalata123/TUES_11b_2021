#ifndef MOVIE_HH
#define MOVIE_HH
#include "string"
#include "media.hh"
using std::string;

class Movie : Media{
    protected:
        unsigned int duration;
        unsigned int watched_minutes;
    public:
        Movie();

        Movie(string, string, unsigned int, unsigned int, unsigned int);

        unsigned int getDuration();
        unsigned int getWatchedTime();
        unsigned int getPrice();

};

#endif