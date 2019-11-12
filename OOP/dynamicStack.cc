#include "iostream"
using namespace std;

class Stack{
    static const int chunk = 2;
    int size, top;
    int* data;
    public:
        Stack(){
            size = chunk;
            data = new int[size];
            top = -1;
        }

        void push(int v){
            if (top >= (size - 1)){
                resize();
            }

            data[++top] = v;
        }

        int pop(){
            if (top < 0){
                throw exception();
            }

            return data[top--];
        }

    private:
        void resize(){
            cout << "Resize begin" << endl;
            int* temp = data;
            data = new int[size + chunk];
            for(int i = 0; i < size; i++){
                data[i] = temp[i];
            }

            size += chunk;
            delete temp;
            cout << "Resize end" << endl;
        }
};


int main(int argc, const char** argv) {
    Stack a = Stack();
    return 0;
}