#include "headers/processStep.hh"

ProcessStep::ProcessStep(int id, string descriotion, vector<BaseMaterial *> materials, int efficiency, Time needed_time) 
: id(id), descriotion(descriotion), materials(materials), efficiency(efficiency), needed_time(needed_time) {};



int ProcessStep::getId(){
    return this->id;
}
string ProcessStep::getDescription(){
    return this->descriotion;
}
vector<BaseMaterial *> ProcessStep::getMaterials(){
    return this->materials;
}
int ProcessStep::getEfficiency(){
    return this->efficiency;
}
Time ProcessStep::getNeededTime(){
    return this->needed_time;
}
