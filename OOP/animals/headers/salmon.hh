#ifndef SALMON_HH
#define SALMON_HH
#include "fish.hh"
#include "can_swim.hh"

class Salmon : public Fish, public Can_swim, public Can_fly{
    public:
        bool tasty();
};

#endif // !SALMON_HH