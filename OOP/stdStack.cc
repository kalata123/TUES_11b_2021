#include <iostream>
#include <stack>
using namespace std;

int main(int argc, char const *argv[])
{
    stack<int> s;

    cout << "empty: " << s.empty() << endl;

    for (int i = 0; i < 10; ++i){
        s.push(i);
    }

    cout << s.top() << endl;

    for (int i = 0; i < 10; ++i){
        s.pop();
    }


    // cout << s.top() << endl;

    return 0;
}

