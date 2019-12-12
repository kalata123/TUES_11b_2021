#ifndef PROCCESSOR_HH
#define PROCCESSOR_HH

#include "baseComponent.hh"

class Proccessor : public BaseComponent{
    protected:
        int cores;
        float freq;
    public:
        Proccessor(){};
        Proccessor(int cores, int freq);
        float get_own_score();
};

#endif