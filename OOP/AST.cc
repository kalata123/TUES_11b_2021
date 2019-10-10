#include "iostream"
#include "string"
#include "fstream"

using namespace std;

/*
int i = 2;
*/

class AST{

    string code;
public:
    AST(string code){
        this->code = code;
    }

    void print(){
        int i = 0, c = this->code.size();
        while (i < c) cout << this->code[i];
    }

};

int main() {

    string code;
    ifstream myf ("testAST");
    //myf.open();
    if (myf.is_open()){

        while ( getline(myf, code)) cout << code << endl;
        myf.close();
    }else cout << "Unable to open" << endl;

    AST A = AST(code);
    // A.print();
    return 0;
}