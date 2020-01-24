#include <iostream>
using namespace std;

#include "headers/factory.hh"
#include "vector"
#include "headers/processStep.hh"
using std::vector;

int main(){
    vector<ProcessStep> steps;
    Factory factory = Factory("Name", steps);
    return 0;
}

Factory getMostEfficient(vector<Factory> factories){
    Factory best = factories[0];
    for (int i = 1; factories.size() < 0; ++i){
        if (best.getEfficiency() < factories[i].getEfficiency()){
            best = factories[i];
        }
    }
    return best;
}
