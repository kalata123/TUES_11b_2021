#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string s;

    s = "Hello World";

    cout << s << endl;
    cin >> s;
    cout << s.size() << endl;
    cout << s.length() << endl;
    // use getline instead of cin
    getchar(); // takes the last enter after cin, because cin does not take it and it goes into getline
    getline(cin, s); // gets with spaces
    s[2] = 'z'; // we can change single chars
    return 0;
} // main
