#include "iostream"
using namespace std;

class Rect{
    public:
        int x, y, w, h;
        
        Rect(int x, int y, int w, int h){
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
        
        int mMIN(int i, int j){
            return (i < j) ? i : j;
        }
        
        int mMAX(int i, int j){
            return (i > j) ? i : j;
        }

        Rect operator+(int i){
            return Rect (x+i, y+i, w+i, h+i);
        }
        
        Rect operator+(Rect r){
            int x1, y1, w1, h1;
            x1 = mMIN (x, r.x);
            y1 = mMIN (y, r.y);
            
            w1 = mMAX (w + x, r.w + r.x) - x;
            h1 = mMAX (h + y, r.h + r.y) - y;
            
            return Rect (x1, y1, w1, h1);
        }        
        
        void operator+=(int i){
            x += i;
            y += i;
            w += i;
            h += i;
        }
        
        void operator+=(Rect r){
            x = mMIN (x, r.x);
            y = mMIN (y, r.y);
            
            w = mMAX (w + x, r.w + r.x) - x;
            h = mMAX (h + y, r.h + r.y) - y;
        }
        
        
        void operator++(){
            x += 1;
            y += 1;
            w += 1;
            h += 1;
        }
        
        void operator++(int){
            x += 1;
            y += 1;
            w += 1;
            h += 1;
        }
        
        Rect operator-(int i){
            if (x-i < 0 || y-i < 0 || w-i < 0 || h-i < 0) 
                throw "Goes beyond zero(0)";
            return Rect (x-i, y-i, w-i, h-i);
        }
        
        /*Rect operator-(Rect r){
            if (r.x-i < 0 || r.y-i < 0 || r.w-i < 0 || r.h-i < 0) 
                throw "Goes beyond zero(0)";
            return Rect (r.x-i, r.y-i, r.w-i, r.h-i);
        }*/
        
        void operator-=(int i){
            // TO BE DONE
        }
        
        void operator-=(Rect r){
            // TO BE DONE
        }
        
        void prnt(){
            cout << "x = " << x << endl
                 << "y = " << y << endl
                 << "w = " << w << endl
                 << "h = " << h << endl;
        }
};


int main (){
    Rect A = Rect (0,0,4,3);
    Rect B = Rect (2,2,5,2);
    Rect C = A + B;
    A += B;
    A.prnt();
    
    return 0;
}
