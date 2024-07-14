/*
* Binary tree
* 
* Author: Farhan Syed
* Year: 2024

  Binary search tree implementation

*/

#include "bintree.h"
#include <iostream>
#include <cmath>

using namespace std;

Node* createNode(int key, double data) {
  Node* newNode = new Node;
  newNode->key = key;
  newNode->data = data;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}

// Insert a new node in the tree
void insert(Node * & p, int key, double to_be_inserted){     
  // Recursively search for where to place the new node
  if (p == nullptr) {  // Base case - no node exists in current position in tree, so correct position has been found and new node is inserted
      p = createNode(key, to_be_inserted);
  } else if(p->key == key){ // Duplicate key, so only update data
      p->data = to_be_inserted;
  }
  else if (key < p->key) { // New node key is less than key of node that p points to, so go left
      insert(p->left, key, to_be_inserted);
  } else {            // New node key is greater than key of node that p points to, so go right
      insert(p->right, key, to_be_inserted); 
  }
}

void remove(Node * & p, const int & key){
  if (p == nullptr) { // Key not found
    throw out_of_range("Key not found!");
  }
  // Search for correct node with matching key
  if (key < p->key) { // Key to be removed is less than current node's key (that p points to), so go left
    remove(p->left, key);
  } else if (key > p->key) { // Key to be removed is greater than current node's key (that p points to), so go right
    remove(p->right, key);
  } 
  // Correct node has been found
  else {                  
    if (p->left == nullptr && p->right == nullptr) { // Leaf node (no children) so node can be easily removed
        delete p;
        p = nullptr;        
    } else if (p->left == nullptr) { // Has right but no left child, so delete the node and move right child to its position
        Node *rightChild = p->right;
        delete p;
        p = rightChild;
    } else if (p->right == nullptr) { // Has left but no right child, so delete the node and move left child to its position
        Node *leftChild = p->left;
        delete p;
        p = leftChild;
    } else { // Node has both left and right children            
        // 1. Find the minimum node in the right subtree 
        Node* minNode = p->right; 
        while (minNode->left != nullptr) {  // traverse through each left node until leaf is reached
          minNode = minNode->left;
        }
        // 2. Replace the current node with the minimum node's key and data 
        p->key = minNode->key; 
        p->data = minNode->data;
        // 3. Remove the minimum node instead, which is a leaf 
        remove(p->right, minNode->key); 
    }
  }
}

// Find the node with key and returns it associated data.
const double & find(Node * p, const int & to_be_found){
  if (p == nullptr) { // Leaf has been reached and key has not been found 
    throw out_of_range("Key not found!");
  }
  if(p->key == to_be_found){ // Key is found, so return the node's data
    return p->data;
  }
  else{
    // If less than current key -> go left. 
    // If greater than current key -> go right
    return (p->key > to_be_found) ? find(p->left, to_be_found) : find(p->right, to_be_found);
  }
}

// Find and return a reference to editable data associated with the key
double & edit(Node * p, const int & to_be_changed){
  if (p == nullptr) { // Leaf has been reached and key has not been found 
      throw out_of_range("Key not found!");
  }
  if(p->key == to_be_changed){ // Key is found, so return the node's data
      return p->data;
  }
  else{
    // If less than current key -> go left. 
    // If greater than current key -> go right
    return (p->key > to_be_changed) ? edit(p->left, to_be_changed) : edit(p->right, to_be_changed);
  }   
}

// Deletes the entire tree at p
void delete_tree(Node * & p){
  if (p != nullptr) {
    delete_tree(p->left);  // Delete all subtrees
    delete_tree(p->right);
    delete p;             // Delete the remaining node 
    p = nullptr;
  } 
}

// Returns the height (longest chain) of the tree
unsigned int max_height(Node * p){
  if (p == nullptr){
    return 0;
  }
  int LHeight = max_height(p->left); // Calculate height of each subtree
  int RHeight = max_height(p->right);

  return (LHeight > RHeight) ? LHeight+1 : RHeight+1; // Height of current node is max height of subtrees plus 1  
}

// Returns the shortest chain of the tree
unsigned int min_height(Node * p){
  if (p == nullptr){
    return 0;
  }
  int LHeight = min_height(p->left); // Calculate height of each subtree
  int RHeight = min_height(p->right);

  return (LHeight < RHeight) ? LHeight+1 : RHeight+1; // Height of current node is min height of subtrees plus 1  
}

// Returns the number of nodes (p included) in the tree
unsigned int size(Node * p){
  if (p == nullptr) { 
    return 0; 
  }
  return size(p->left) + size(p->right) + 1; // Size of tree is sum of sizes of subtrees, plus 1 for the root node
}

// Returns true if the tree is balanced
bool is_balanced(Node * p){  
  if (p == nullptr) {
      return true; 
  }
  // In a balanced tree, the heights of the subtrees of every node can only differ by 1  
  int LHeight = max_height(p->left);
  int RHeight = max_height(p->right);
  return (abs(LHeight - RHeight) <= 1 && is_balanced(p->left) && is_balanced(p->right)); // Check that current node and both subtrees are balanced  
}