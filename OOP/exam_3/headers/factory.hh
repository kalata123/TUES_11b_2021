#ifndef FACTORY_HH
#define FACTORY_HH
#include "string"
#include "vector"
#include "processStep.hh"
#include "baseMaterial.hh"
using std::string;
using std::vector;
using std::pair;
using std::exception;

class ProcessStep;
class BaseMaterial;

class Factory{
    protected:
        string name;
        vector<ProcessStep> productionProcessSteps;
    public:
        class ErrorNoMaterialsOrTime: public exception {};
        class ErrorNoDefinedSteps: public exception {};
        class ErrorEfficiencyLessThan5: public exception {};

        Factory(string, vector<ProcessStep>);

        string getName();
        void addNewProcessStep(vector<BaseMaterial *>, string, Time, int);
        pair<vector<BaseMaterial *>, Time> getUsedMaterialsAndTime();
        int getEfficiency();
        string getReport();
};

#endif