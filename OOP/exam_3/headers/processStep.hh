#ifndef PROCESSSTEP_HH
#define PROCESSSTEP_HH
#include "string"
#include "vector"
#include "time.hh"
#include "baseMaterial.hh"
using std::string;
using std::vector;

class BaseMaterial;
class Time;

class ProcessStep{
    protected:
        int id;
        string descriotion;
        vector<BaseMaterial *> materials;
        int efficiency;
        Time needed_time;
    public:
        ProcessStep(int, string, vector<BaseMaterial *>, int, Time);

        int getId();
        string getDescription();
        vector<BaseMaterial *> getMaterials();
        int getEfficiency();
        Time getNeededTime();

};

#endif