#include "iostream"
#include "list"
#include "set"
#include "string"
#include "sstream"
using namespace std;

class Point {
    private:
        ostringstream data;
    public:

        void setCoordinates(int x, int y){
            this->data.str("");
            this->data << "(" << x << ", " << y << ")";
        }

        string toString(){
            return data.str();
        }
};

class CollectionPoints{
    private:
        list<Point> data;
    public:

        void readPoint(){
            ostringstream input;
            string coords;
            int x, y;
            while(1){
                getline(coords);
                if (strcmp(coords,"") == 0){
                    break;
                }
                x = to_int(coords[1]);
                y = to_int(coords[4]);
                input << "(" << x << ", " << y << ")";
            }

        }
}

int main(int argc, const char** argv) {
    Point p = Point();
    p.setCoordinates(1,2);
    cout << p.toString() << endl;

    CollectionPoints collection = CollectionPoints();
    return 0;
}