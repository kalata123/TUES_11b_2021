#ifndef NODE_HH
#define NODE_HH
#include "string"
using std::string;

template<class T>
class Node{
    protected:
        Node *left;
        Node *right;

        T value;
    public:
        Node(T value) : value(value), left(0), right(0) {};

        T getValue(){
            return value;
        }

        void addChildNode(Node<T> *child){
            if (child->getValue() > value)
            {
                if (right == 0)
                {
                    right = child;
                } else
                {
                    right->addChildNode(child);
                }
            } else 
            {
                if (left == 0)
                {
                    left = child;
                } else
                {
                    left->addChildNode(child);
                }
            }
        }

        void print(int level = 0){
            std::cout << value << std::endl;

            if (left != 0) {
                for(int i = 0; i < level; i++)
                {
                    std::cout << "|  ";
                }
                std::cout << "+--";
                left->print(level+1);
            }
            if (right != 0) {
                for(int i = 0; i < level; i++)
                {
                    std::cout << "|  ";
                }
                std::cout << "*--";
                right->print(level+1);
            }
        }

};


#endif