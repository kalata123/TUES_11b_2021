#ifndef GAME_HH
#define GAME_HH
#include "string"
#include "media.hh"
using std::string;

class Game : Media{
    protected:
        unsigned int played_hours;
    public:
        Game();

        Game(string, string, unsigned int, unsigned int);

        unsigned int getPlayedHours();
        unsigned int getPrice();
};

#endif