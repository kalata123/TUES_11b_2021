#include "iostream"
#include "string"
#include "list"
using namespace std;

class CarCatalogue {
    private:
        string name;
        list<string> models;
        list<string>::iterator it;

    public:
        CarCatalogue(){}
        CarCatalogue(string name, list<string> models){
            if (models.size() < 5) throw "Fk1";
            for (this -> it = models.begin(); this -> it != models.end(); this -> it++){
                if (*this -> it == "") cout << "Fk2" << endl;
            }
            for (this -> it = models.begin(); this -> it != models.end() --; this -> it++){
                list<string>::iterator lt;
                for (lt = this -> it++; lt != models.end(); lt++){
                    if (*lt == *this -> it) cout << "Fk3" << endl;
                    cout << "Fk5" << endl;
                }
            }
            this -> name = name;
            this -> models = models;
        } 

        string getBrand(){
            return this -> name;
        }

        list<string> getModels(){
            return this -> models;
        }

        int hasModel(string theModel){
            for (this -> it = this -> models.begin(); this -> it != this -> models.end(); this -> it++){
                if (*this -> it == theModel){
                    return 1;
                }
            }
            return 0;
        }

        void addModel(string model_name){
            if (!hasModel(model_name)){
                this -> it = this -> models.end();
                this -> models.insert(this -> it++, model_name);
            }
        }

};


int main(int argc, char const *argv[])
{
    CarCatalogue catalogue = CarCatalogue("MyCatalogue", {"m1", "m5", "m4", "m3", "m2"});
    cout << catalogue.getBrand() << endl;
    list<string> li = catalogue.getModels();
    list<string> ::iterator it;
    for (it = li.begin(); it != li.end(); it ++)
        cout << *it << endl;
    return 0;
}
