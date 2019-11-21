#ifndef CHARACTER_HH
#define CHARACTER_HH
#include "entity.hh"
class Character  : public Entity{
    int sth;
    public:
        Character();
        Character(int sth);
};
#endif // !CHARACTER_HH