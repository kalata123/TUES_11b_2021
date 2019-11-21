#include "manager.h"
using std::string;

Manager::Manager(){
    level = 0;
}

Manager::Manager(string name, int id, int level){
    level = 0;
}

void Manager::setLevel(int level){
    Manager::level = level;
}