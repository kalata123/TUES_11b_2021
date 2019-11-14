#include "iostream"
using namespace std;

class FibNum{
    int arr;
    int len = 0;

    public:
        FibNum(){}
        FibNum(int numbr){
            arr = new int[numbr];
            genFN(numbr);
        }

        void genFN(int fnum){
            int a = 0;
            int b = 1;
            for (int i = 0; i < fnum; i++){
            }
        }

};

int main(int argc, const char** argv) {
    return 0;
}