#include "bintree.h"
#include <iostream>

using namespace std;

// Compile: g++ -o main main.cpp

template<typename S, typename T>
void print_inorder(Node<S, T> * p) {
    if (p != nullptr) {
        print_inorder(p->getLeft());
        cout << p->data << endl;
        print_inorder(p->getRight());
    }
}

int main() {
    Node<int, int>* root = createNode(100,10);
    
    insert(root,200,20);
    insert(root,500,50);    
    insert(root,400,40);
    insert(root,90,9);
    insert(root,60,6);
    insert(root,700,70);
    insert(root,300,30);
    insert(root,800,80);
    insert(root,20,2);

    // Iterator in-order using print function
    cout << "Iterator in-order using print function \n";
    print_inorder(root);

    // Iterator in-order using for loop
    cout << "Iterator in-order using loop \n";
    for (NodeIterator<int, int> p = root->begin(); p != root->end(); ++p) {
        std::cout << *p << endl;
    }

    // Const iterator in-order
    cout << "Const iterator in-order \n";
    const Node<int, int>* constRoot = root;
    for (ConstNodeIterator<int, int> q = constRoot->cbegin(); q != constRoot->cend(); ++q) {
        std::cout << *q << endl;
    }

    // Iterator reverse in-order
    cout << "Iterator reverse in-order \n";
    for (NodeIterator<int, int> p = root->rbegin(); p != root->rend(); ++p){
        cout << *p << endl;
    }

    delete_tree(root);

    return 0;
}
