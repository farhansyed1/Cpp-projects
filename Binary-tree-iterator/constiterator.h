/*
* Iterator for binary tree
* 
* Author: Farhan Syed
* Year: 2024

  Const iterator template with implementations
*/

#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include "node.h"

#include <utility> 
#include <stdexcept> 
#include <stack>

template <class S, class T>
struct Node; 

template <class S, class T>
struct ConstNodeIterator {
    using iterator_category = std::forward_iterator_tag; // Inherit forward iterator
    using value_type = Node<S, T>;
    using pointer = Node<S, T>*;
    using reference = Node<S, T>&;
    
    const Node<S, T>* currentNode;
    std::stack<const Node<S, T>*> nodeStack;
    bool reverse;

    ConstNodeIterator(const Node<S, T>* root, bool rev);
    ConstNodeIterator(const ConstNodeIterator& other);

    ConstNodeIterator& operator=(const ConstNodeIterator& other);
    const Node<S, T>& operator*() const;
    const Node<S, T>* operator->() const;
    ConstNodeIterator& operator++();
    ConstNodeIterator operator++(int);
    bool operator==(const ConstNodeIterator& other) const;
    bool operator!=(const ConstNodeIterator& other) const;
};

// Constructor for the iterator. Parameters: node that iterator starts pointing to, type of iterator (true = forward, false = reverse)
template <class S, class T>
ConstNodeIterator<S, T>::ConstNodeIterator(const Node<S, T>* root, bool rev) : currentNode(root), reverse(rev) {
    // Reverse: Push all nodes from root to right side onto the stack
    if (reverse) {
        while (currentNode != nullptr) {
            nodeStack.push(currentNode);
            currentNode = currentNode->right;
        }
    } 
    // Forward: Push all nodes from root to left side onto the stack
    else {
        while (currentNode != nullptr) {
            nodeStack.push(currentNode);
            currentNode = currentNode->left;
        }
    }
    // Pointer set to top of the stack
    if (!nodeStack.empty()) {
        currentNode = nodeStack.top();
    } else {
        currentNode = nullptr;
    }
}

// Copy constructor 
template <class S, class T>
ConstNodeIterator<S, T>::ConstNodeIterator(const ConstNodeIterator<S, T>& other) : currentNode(other.currentNode), nodeStack(other.nodeStack) {}

// Assignment operator 
template <class S, class T>
ConstNodeIterator<S, T>& ConstNodeIterator<S, T>::operator=(const ConstNodeIterator<S, T>& other) {
    if (this != &other) {
        currentNode = other.currentNode;
        nodeStack = other.nodeStack;
    }
    return *this;
}

// Dereference (*) operator 
template <class S, class T>
const Node<S, T>& ConstNodeIterator<S, T>::operator*() const  {
    if (!currentNode) throw std::out_of_range("Node out of range!");
    return *currentNode;
}

// Arrow (->) operator
template <class S, class T>
const Node<S, T>* ConstNodeIterator<S, T>::operator->() const {
    if (!currentNode) throw std::out_of_range("Node out of range!");
    return currentNode;
}

// Equality comparison
template <class S, class T>
bool ConstNodeIterator<S, T>::operator==(const ConstNodeIterator& other) const {
    return currentNode == other.currentNode;
}

// Inequality comparison
template <class S, class T>
bool ConstNodeIterator<S, T>::operator!=(const ConstNodeIterator& other) const {
    return currentNode != other.currentNode;
}

// Prefix increment - Iterator pointer moves to next node
template <class S, class T>
ConstNodeIterator<S, T>& ConstNodeIterator<S, T>::operator++() {
    if (!nodeStack.empty()) {
        const Node<S, T>* node = nodeStack.top();
        nodeStack.pop();
        const Node<S, T>* next = reverse ? node->left : node->right; // Next node is to the left for forward iterator, and right for reversed. 
        while (next != nullptr) {
            nodeStack.push(next);
            next = reverse ? next->right : next->left; // Push all nodes from root to left/right side onto the stack
        }
        currentNode = nodeStack.empty() ? nullptr : nodeStack.top(); // Update current node
    }
    return *this;
}

// Postfix increment - Iterator pointer moves to next node but old value is returned
template <class S, class T>
ConstNodeIterator<S, T> ConstNodeIterator<S, T>::operator++(int) {
    ConstNodeIterator tmp(*this);
    ++(*this);          // Iterator position is incremented 
    return tmp;         // Return old position
}

// Friend swap function - swap two iterators
template <class S, class T>
void swap(ConstNodeIterator<S, T>& first, ConstNodeIterator<S, T>& second) {
    std::swap(first.currentNode, second.currentNode);
    std::swap(first.nodeStack, second.nodeStack);
}

#endif //CONSTITERATOR_H
