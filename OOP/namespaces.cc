#include <iostream>
using namespace std;

namespace firstSpace {
    void say_hello(){
        cout<<"Hello World"<<endl;
    }
} // namespace firstSpace


namespace secondSpace {
    void say_hello(){
        cout<<"Hello There"<<endl;
    }
    namespace innerSpace
    {
        void say_hello(){
            cout << "Hello innerSpace" << endl;
        }
    } // namespace innerSpace
    
} // namespace secondSpace

using namespace firstSpace;

int main (){
    say_hello();
    secondSpace::say_hello();
}