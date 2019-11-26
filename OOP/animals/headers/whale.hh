#ifndef WHALE_HH
#define WHALE_HH
#include "mammal.hh"
#include "can_swim.hh"

class Whale : public Mammal, public Can_swim{
    public:
        void oooo();
};

#endif // !WHALE_HH