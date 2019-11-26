#ifndef SEAGULL_HH
#define SEAGULL_HH
#include "bird.hh"
#include "can_fly.hh"

class Seagull : public Bird, public Can_fly{
    public:
        bool eatTrash();
};

#endif // !SEAGULL_HH