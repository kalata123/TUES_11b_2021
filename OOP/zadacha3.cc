#include "iostream"
#include "string"
#include "vector"
using namespace std;

class Animal {
    public:
        const string name;
        short age;
        string kind;
        Animal(string name, short age, string kind) : name(name), age(age), kind(kind) {}
};

class Cat : public Animal {
    public:
        Cat(string name, short age) : Animal(name, age, "cat"){}
};

class Dog : public Animal {
    public:
        Dog(string name, short age) : Animal(name, age, "dog"){}
};

class Shellter {
    private:
        Shellter(){}
    public:
        static vector<Animal> animals;

        static void addAnimal(string kind, string name, short age){
            Animal a = Animal(name, age, kind);
            animals.push_back(a);
        }

        static Animal& findAnimal(string kind, string name, short age){ // could be returning type auto
            Animal a = Animal(name, age, kind);
            for (int i = 0; i < animals.size(); i++){
                if (animals[i].age == a.age && animals[i].name == a.name && animals[i].kind == a.kind){
                    return animals[i];
                }
            }
        }
};

vector<Animal> Shellter::animals = {};
// vector<Cat> Shellter::cats = {};
// vector<Dog> Shellter::dogs = {};

int main(int argc, char const *argv[])
{
    Shellter::addAnimal("cat", "Pesho", 1);
    Shellter::addAnimal("cat", "ALELUYA", 1);
    Shellter::addAnimal("dog", "GOsho", 4);
    // Animal a = ;
    cout << Shellter::findAnimal("cat", "ALELUYA", 1).name << endl; 
    return 0;
}
