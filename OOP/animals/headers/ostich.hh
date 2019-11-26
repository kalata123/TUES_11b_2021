#ifndef OSTICH_HH
#define OSTICH_HH
#include "bird.hh"
#include "can_walk.hh"

class Ostich : public Bird, public Can_walk{
    public:
        bool bigEggs();
};

#endif // !OSTICH_HH