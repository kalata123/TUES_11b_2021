#include <iostream>
#include "list"
using namespace std;

void print_list(list<int> l){
    list<int>::iterator it; // used for iterating vectors lists and so on...
    for (it = l.begin(); it != l.end(); it++){
        cout << *it << endl;
    }
}

int main(int argc, char const *argv[])
{
    list<int> l; // linkedList

    for (int i = 0; i < 10; i++)
    {   
        l.push_back(i);
    }

    print_list(l);
    

    return 0;
}