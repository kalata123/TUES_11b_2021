#ifndef LION_HH
#define LION_HH
#include "mammal.hh"
#include "can_walk.hh"

class Lion : public Mammal, public Can_walk {
    public:
        void roar();
};

#endif // !LION_HH