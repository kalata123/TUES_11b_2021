#ifndef SONG_HH
#define SONG_HH
#include "string"
#include "media.hh"
using std::string;

class Song : Media{
    protected:
        unsigned int times_listened;
    public:
        Song();

        Song(string, string, unsigned int, unsigned int);

        unsigned int getTimesListened();
        unsigned int getPrice();
};

#endif