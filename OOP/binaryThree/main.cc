#include <iostream>
using namespace std;

#include "headers/binaryTree.hh"

int main(){
    BinaryTree<int> tree = BinaryTree<int>();

    tree.addValue(5);
    tree.addValue(3);
    tree.addValue(2);
    tree.addValue(6);
    tree.addValue(5);
    tree.addValue(3);
    tree.addValue(2);
    tree.addValue(6);

    tree.print();
    return 0;
}