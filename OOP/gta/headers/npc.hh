#ifndef NPC_HH
#define NPC_HH
#include "character.hh"
class Npc : public Character{
    int sth;
    public:
        Npc();
        Npc(int sth);
};
#endif // !NPC_HH