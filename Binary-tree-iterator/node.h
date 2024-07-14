/*
* Iterator for binary tree
* 
* Author: Farhan Syed
* Year: 2024

  Node template with implementations
*/

#ifndef NODE_H
#define NODE_H


// Forward declaration of the iterators
template <class S, class T> struct Node;
template <class S, class T> struct NodeIterator;
template <class S, class T> struct ConstNodeIterator;

// Forward declarations of the bintree functions
template<typename S, typename T>
Node<S, T>* createNode(S key, T data);

template<typename S, typename T>
void insert(Node<S, T>* &p, S key, T to_be_inserted);

template<typename S, typename T>
void remove(Node<S, T>* &p, const S &key);

template<typename S, typename T>
void delete_tree(Node<S, T>* &p);

template<typename S, typename T>
const T& find(Node<S, T>* p, const S& to_be_found);

template<typename S, typename T>
T& edit(Node<S, T>* p, const S& to_be_changed);

template<typename S, typename T>
unsigned int max_height(Node<S, T>* p);

template<typename S, typename T>
unsigned int min_height(Node<S, T>* p);

template<typename S, typename T>
unsigned int size(Node<S, T>* p);

template<typename S, typename T>
bool is_balanced(Node<S, T>* p);

template <class S, class T>
struct Node {
    typedef NodeIterator<S, T> iterator;
    typedef ConstNodeIterator<S, T> const_iterator;

    S key;
    T data;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;    
    iterator rbegin();
    iterator rend();

    Node<S, T>* getLeft() const { return left; }
    Node<S, T>* getRight() const { return right; }

    friend struct NodeIterator<S, T>;
    friend struct ConstNodeIterator<S, T>;

    friend Node<S, T>* createNode<S, T>(S, T);
    friend void insert<S, T>(Node<S, T>*&, S, T);
    friend void remove<S, T>(Node<S, T>*&, const S&);
    friend void delete_tree<S, T>(Node<S, T>*&);
    friend const T& find<S, T>(Node<S, T>*, const S&);
    friend T& edit<S, T>(Node<S, T>*, const S&);
    friend unsigned int max_height<S, T>(Node<S, T>*);
    friend unsigned int min_height<S, T>(Node<S, T>*);
    friend unsigned int size<S, T>(Node<S, T>*);
    friend bool is_balanced<S, T>(Node<S, T>*);

    private: 
        Node<S, T>* parent;
        Node<S, T>* right;
        Node<S, T>* left;
};

#include "iterator.h"
#include "constiterator.h"

// Output operator
template <class S, class T>
std::ostream& operator<<(std::ostream& os, const Node<S, T>& node) {
    os << node.data;
    return os;
}

// begin() - returns beginning of forward iterator (leftmost node)
template <class S, class T>
typename Node<S, T>::iterator Node<S, T>::begin() {
    return iterator(this, false);
}

// end() - returns end of forward iterator (nullptr)
template <class S, class T>
typename Node<S, T>::iterator Node<S, T>::end() {
    return iterator(nullptr, false); 
}

// rbegin() - returns beginning of reverse iterator (rightmost node)
template <class S, class T>
typename Node<S, T>::iterator Node<S, T>::rbegin() {
    return iterator(this, true);
}

// rbegin() - returns end of reverse iterator (nullptr)
template <class S, class T>
typename Node<S, T>::iterator Node<S, T>::rend() {
    return iterator(nullptr, true);
}

// cbegin() - returns beginning of const forward iterator (leftmost node)
template <class S, class T>
typename Node<S, T>::const_iterator Node<S, T>::cbegin() const {
    return ConstNodeIterator<S, T>(this, false); 
}

// cend() - returns end of const forward iterator (nullptr)
template <class S, class T>
typename Node<S, T>::const_iterator Node<S, T>::cend() const {
    return ConstNodeIterator<S, T>(nullptr, false); 
}

#endif //NODE_H
