#ifndef TRAIN_HH
#define TRAIN_HH
#include "land.hh"
class Train : public Land{
    int sth;
    public:
        Train();
        Train(int sth);
};

#endif // !TRAIN_HH