#ifndef STACK_HH
#define STACK_HH

template<class T>
class Stack{
    protected:
        static const unsigned int chunk = 2;
        int size;
        T* data;
        int top;
    public:
        Stack();
        Stack(const Stack&);
        ~Stack();
        Stack& operator=(const Stack&);
        void push(const T&);
        T pop();
    private:
        void resize();

};

#endif