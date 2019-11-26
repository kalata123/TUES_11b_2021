#ifndef WHALE_HH
#define WHALE_HH
#include "fish.hh"
#include "can_swim.hh"
#include "can_fly.hh"

class FlyingFish : public Fish, public Can_swim, public Can_fly{
    public:
        void runAway();
};

#endif // !WHALE_HH