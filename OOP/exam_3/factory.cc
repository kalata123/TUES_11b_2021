#include "headers/factory.hh"

Factory::Factory(string name, vector<ProcessStep> productionProcessSteps) 
: name(name), productionProcessSteps(productionProcessSteps) {};


string Factory::getName(){
    return this->name;
}


void Factory::addNewProcessStep(vector<BaseMaterial *> materials, string desc, Time time, int eff){
    if (materials.size() < 1 || time.getQuantity()){
        throw ErrorNoMaterialsOrTime();
    }
    ProcessStep step = ProcessStep(this->productionProcessSteps.size(), desc, materials, eff, time);
    productionProcessSteps.push_back(step);
}


pair<vector<BaseMaterial *>, Time> Factory::getUsedMaterialsAndTime(){
    Time time = Time(0);
    vector<BaseMaterial *> materialsUsed;
    for (int i = 0; i < productionProcessSteps.size(); ++i){
        for (int j = 0; j < productionProcessSteps[i].getMaterials().size(); ++j){
            materialsUsed.push_back(productionProcessSteps[i].getMaterials()[j]);
        }
        time.addTime(productionProcessSteps[i].getNeededTime().getQuantity());
    }
    pair<vector<BaseMaterial *>, Time> paired = std::make_pair(materialsUsed, time);
    return paired;
}


int Factory::getEfficiency(){
    if(productionProcessSteps.size() < 1) {
        throw ErrorNoDefinedSteps();
    }
    int efficiency = 0; 
    for (int i = 0; i < productionProcessSteps.size(); ++i){
        if (productionProcessSteps[i].getEfficiency() < 5){
            efficiency += productionProcessSteps[i].getEfficiency();
        }
    }
}


string Factory::getReport(){
    string report = this->name;
    pair<vector<BaseMaterial *>, Time> paired = getUsedMaterialsAndTime();
    int efficiency = getEfficiency();
    report += " Materials:";
    for (int i = 0; i < paired.first.size(); ++i){
        report += paired.first[i]->getName();
        report += "\n";
    }
    report += "Efficiency: ";
    report += std::to_string(efficiency);

}