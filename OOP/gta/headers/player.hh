#ifndef PLAYER_HH
#define PLAYER_HH
#include "character.hh"
class Player : public Character{
    int sth;
    public:
        Player();
        Player(int sth);
};
#endif // !PLAYER_HH