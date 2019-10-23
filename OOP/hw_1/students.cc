#include "iostream"
#include "list"
using namespace std;

class StudentInfo {
    private:
        string name;
        list<double> marks;

    public:

        string getName(){
            return this->name;
        }

        list<double> getMarks(){
            return this->marks;
        }

        void addMark(double new_mark){
            this->marks.push_back(new_mark);
        }

};

int main(int argc, char const *argv[])
{

    return 0;
}
