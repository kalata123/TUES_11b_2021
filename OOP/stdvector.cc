#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> v;

    for (int i = 0; i < 33; i++)
    {
        v.push_back(i);
    }

    cout << "Size: " << v.size() << endl;
    cout << "capacity: " << v.capacity() << endl;
    
    v.pop_back();
    // print_vector(v); // define your own namespace
    return 0;
}
