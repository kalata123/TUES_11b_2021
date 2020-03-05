#ifndef BINARYTREE_HH
#define BINARYTREE_HH
#include "string"
#include "node.hh"
using std::string;

// template<class T>
// class Node;

template<class T>
class BinaryTree{
    protected:
        
        Node<T> * root;
    public:
        BinaryTree() : root(0){};

        void addValue(T value) {
            if (root == 0){
                root = new Node<T>(value);
            }else
            {
                root->addChildNode(new Node<T>(value));
            }    
        };

        void print(){
            if (root == 0) return;
            root->print();
        }

};



#endif