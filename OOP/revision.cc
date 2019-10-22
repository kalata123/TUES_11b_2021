#include "iostream"
#include "vector"
#include "string"
#include "sstream"
#include "algorithm"6
using namespace std;

class Contestant {
    
    string name;
    
};

bool compareContestant(Contestant contestant1, Contestant contestant2){
    return contestant1.getDistance() < contestant2.getDistance();
}

class Race {
    vector<Contestant> contestants;
    
    public:
        
        Race(){}
        
        Race(vector<Contestant> contestants) {
            this -> contestants = contestants;
        }

        void simulateRace(int iterations_count) {
            resetContestants();
            for (int i = 0; i < contestants.size(); i++){
                contestants[i].calcDistance(iterations_count);
            }
            
            sort(contestants.begin(), contestants.end(), compareContestants);
        }

        string toString(){
            ostringstream out;
            for(int i = 0; i < contestants.size(); i++){
                out << 
                contestants[i].getName() << ": " <<
                contestants[i].getSpeed() << '(' << 
                contestants[i].getSpeed() << ")" << endl;
            }
            returnt out.str; 
        }
};


int main() {

    return 0;
}





