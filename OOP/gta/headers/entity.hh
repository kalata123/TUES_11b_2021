#ifndef ENTITY_HH
#define ENTITY_HH
#include "base.hh"
class Entity  : public BaseOBJ{
    int sth;
    public:
        Entity();
        Entity(int sth);
};
#endif // !ENTITY_HH