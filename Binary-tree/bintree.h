/*
* Binary tree
* 
* Author: Farhan Syed
* Year: 2024

  Binary tree header file
*/

#ifndef BINTREE_H
#define BINTREE_H

struct Node {
    int key;
    double data;
    Node * right;
    Node * left;
};

Node* createNode(int key, double data);
void insert(Node * & p, int key, double to_be_inserted);  // Note: reference to pointer
void remove(Node * & p, const int & key);
const double & find(Node * p, const int & to_be_found);
double & edit(Node * p, const int & to_be_changed);
void delete_tree(Node * & p);

unsigned int max_height(Node * p);
unsigned int min_height(Node * p);
unsigned int size(Node * p);
bool is_balanced(Node * p);

#endif //BINTREE_H