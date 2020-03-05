#ifndef TIME_HH
#define TIME_HH
#include "string"
#include "baseMaterial.hh"
using std::string;

class Time: public BaseMaterial{
    protected:        
    public:
        Time(int time) : BaseMaterial("Time", "None", time){}
        void addTime(int new_quantity) {
            this->quantity += new_quantity; 
        }
};

#endif