#include "iostream"
#include "vector"
#include "sstream"
#include "string"
#include "algorithm"

using namespace std;

class Contestant{
    private:
        string name;
        double speed, distance = 0;
    
    public:
        Contestant(){
            this->speed = 0;
        }

        Contestant(double speed, string name){
            this->speed = 0;
            this->name = name;
        }

        string getName(){
            return this->name;
        }

        double getSpeed(){
            return this->speed;
        }

        double getDistance(){
            return this->distance;
        }

        void calcDistance(int iteration_count){
            this->distance = this->speed * iteration_count;
        }
        
        void setDistToZero(){
            this->distance = 0;
        }
};

bool compareContestants(Contestant contestant1, Contestant contestant2){
    return contestant1.getDistance() > contestant2.getDistance();
}

class Race{
    private:
        vector<Contestant> contestants;
        vector<Contestant>::iterator cit;
    public:
        Race(){
            this->contestants.clear();
        }

        Race(vector<Contestant> contestants){
            this->contestants = contestants;
        }

        vector<Contestant> getContestants(){
            return this->contestants;
        }

        void addContestant(Contestant new_contestant){
            this->contestants.push_back(new_contestant);
        }

        void resetContestants(){
            for (this->cit = this->contestants.begin(); this->cit != this->contestants.end(); cit++){
                this->cit->setDistToZero();
            }
        }

        string getContestantStanding(){
            ostringstream s;
            for (int i = 0; i < this->contestants.size(); i++){
                s << this->contestants[i].getName() << ": " << 
                     this->contestants[i].getDistance() << "(" << 
                     this->contestants[i].getSpeed() << ")" << endl;
            }
            return s.str();
        }

        void simulateRace(int iteration_count){
            this->resetContestants();
            cout << getContestantStanding() << endl;

            for (int i = 0; i < this->contestants.size(); i++){
                this->contestants[i].calcDistance(iteration_count);
            }

            sort(this->contestants.begin(), this->contestants.end(), [](Contestant c1, Contestant c2) {return c1.getDistance() > c2.getDistance();});
            cout << getContestantStanding() << endl;
        }

};

int main(int argc, char const *argv[])
{
    vector<Contestant> li = {Contestant(1,"1"), Contestant(2,"2")};
    Race race = Race(li);
    race.simulateRace(5);
    return 0;
}
