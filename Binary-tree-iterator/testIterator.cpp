#include "bintree.h"
#include <gtest/gtest.h>

// To compile: g++ -o testIterator.exe testIterator.cpp -lgtest -lgtest_main -pthread
// Running valgrind: valgrind --leak-check=full --show-leak-kinds=all ./testIterator.exe

using namespace std;

// ITERATION

TEST(ForwardIterator, iteration) {
    Node<int, int>* t = createNode(5,5);
    
    insert(t,2,2);
    insert(t,4,4);
    insert(t,9,9);
    insert(t,6,6);
    insert(t,7,7);
    insert(t,3,3);
    insert(t,8,8);
    insert(t,1,1);
    int count = 1;
    for (NodeIterator<int, int> p = t->begin(); p != t->end(); ++p) {
        EXPECT_EQ((*p).data, count);
        EXPECT_EQ(p->data, count);
        count++;
    }

    delete_tree(t);
}

TEST(ConstIterator, iteration) {
    Node<int, int>* t = createNode(5,5);
    
    insert(t,2,2);
    insert(t,4,4);
    insert(t,9,9);
    insert(t,6,6);
    insert(t,7,7);
    insert(t,3,3);
    insert(t,8,8);
    insert(t,1,1);
    int count = 1;
    for (ConstNodeIterator<int, int> p = t->cbegin(); p != t->cend(); ++p) {
        EXPECT_EQ((*p).data, count);
        EXPECT_EQ(p->data, count);
        count++;
    }

    delete_tree(t);
}

TEST(ReverseIterator, reverseIteration) {
    Node<int, int>* t = createNode(5, 5);
    insert(t, 3, 3);
    insert(t, 7, 7);
    insert(t, 2, 2);
    insert(t, 4, 4);
    insert(t, 6, 6);
    insert(t, 8, 8);

    vector<int> expected = {8, 7, 6, 5, 4, 3, 2};
    vector<int> results;
    for (NodeIterator<int, int> p = t->rbegin(); p != t->rend(); ++p) {
        results.push_back(p->data);
    }

    EXPECT_EQ(results, expected);

    delete_tree(t);
}

// DEREFERENCING

TEST(ForwardIterator, deferencing) {
    Node<int, int>* t = createNode(10, 100);
    insert(t, 5, 50);

    NodeIterator<int, int> it = t->begin();
    
    // Valid
    EXPECT_EQ((*it).data, 50);  
    EXPECT_EQ(it->data, 50);    
    
    ++it;              
    EXPECT_EQ((*it).data, 100);  
    EXPECT_EQ(it->data, 100);    

    // Invalid
    it = t->end();  
    EXPECT_THROW({*it;}, out_of_range);
    EXPECT_THROW({it->data;}, out_of_range);

    delete_tree(t);
}

TEST(ConstIterator, deferencing) {
    Node<int, int>* t = createNode(10, 100);
    insert(t, 5, 50);

    ConstNodeIterator<int, int> it = t->cbegin();
    
    // Valid
    EXPECT_EQ((*it).data, 50);  
    EXPECT_EQ(it->data, 50);    
    
    ++it;              
    EXPECT_EQ((*it).data, 100);  
    EXPECT_EQ(it->data, 100);    

    // Invalid
    it = t->cend();  
    EXPECT_THROW({*it;}, out_of_range);
    EXPECT_THROW({it->data;}, out_of_range);

    delete_tree(t);
}

TEST(ReverseIterator, deferencing) {
    Node<int, int>* t = createNode(10, 100);
    insert(t, 5, 50);

    NodeIterator<int, int> it = t->rbegin();
    
    // Valid
    EXPECT_EQ((*it).data, 100);  
    EXPECT_EQ(it->data, 100);    

    ++it;              
    EXPECT_EQ((*it).data, 50);  
    EXPECT_EQ(it->data, 50);      

    // Invalid
    it = t->rend();  
    EXPECT_THROW({*it;}, out_of_range);
    EXPECT_THROW({it->data;}, out_of_range);

    delete_tree(t);
}

// COPYING

TEST(ForwardIterator, copying) {
    Node<int, int>* t = createNode(10, 100);
    insert(t, 5, 50);
    insert(t, 15, 150);

    NodeIterator<int, int> original = t->begin();
    NodeIterator<int, int> copyWithConstructor(original);
    NodeIterator<int, int> copyWithOperator = original;  

    EXPECT_EQ((*original).data, (*copyWithConstructor).data);
    EXPECT_EQ((*original).data, (*copyWithOperator).data);

    EXPECT_EQ(original->data, copyWithConstructor->data);
    EXPECT_EQ(original->data, copyWithOperator->data);

    // Incrementing original should not affect copies
    ++original;
    EXPECT_NE((*original).data, (*copyWithConstructor).data);
    EXPECT_NE((*original).data, (*copyWithOperator).data);

    EXPECT_NE(original->data, copyWithConstructor->data);
    EXPECT_NE(original->data, copyWithOperator->data);

    delete_tree(t);
}

TEST(ConstIterator, copying) {
    Node<int, int>* t = createNode(10, 100);
    insert(t, 5, 50);
    insert(t, 15, 150);

    ConstNodeIterator<int, int> original = t->cbegin();
    ConstNodeIterator<int, int> copyWithConstructor(original);
    ConstNodeIterator<int, int> copyWithOperator = original;  

    EXPECT_EQ((*original).data, (*copyWithConstructor).data);
    EXPECT_EQ((*original).data, (*copyWithOperator).data);

    EXPECT_EQ(original->data, copyWithConstructor->data);
    EXPECT_EQ(original->data, copyWithOperator->data);

    // Incrementing original should not affect copies
    ++original;
    EXPECT_NE((*original).data, (*copyWithConstructor).data);
    EXPECT_NE((*original).data, (*copyWithOperator).data);

    EXPECT_NE(original->data, copyWithConstructor->data);
    EXPECT_NE(original->data, copyWithOperator->data);

    delete_tree(t);
}

TEST(ReverseIterator, copying) {
    Node<int, int>* t = createNode(10, 100);
    insert(t, 5, 50);
    insert(t, 15, 150);

    NodeIterator<int, int> original = t->rbegin();
    NodeIterator<int, int> copyWithConstructor(original);
    NodeIterator<int, int> copyWithOperator = original;  

    EXPECT_EQ((*original).data, (*copyWithConstructor).data);
    EXPECT_EQ((*original).data, (*copyWithOperator).data);

    EXPECT_EQ(original->data, copyWithConstructor->data);
    EXPECT_EQ(original->data, copyWithOperator->data);

    // Incrementing original should not affect copies
    ++original;
    EXPECT_NE((*original).data, (*copyWithConstructor).data);
    EXPECT_NE((*original).data, (*copyWithOperator).data);

    EXPECT_NE(original->data, copyWithConstructor->data);
    EXPECT_NE(original->data, copyWithOperator->data);

    delete_tree(t);
}

// EQUALITY AND INEQUALITY

TEST(ForwardIterator, equalityAndInequality) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 5, 5);

    NodeIterator<int, int> it1 = t->begin();  
    NodeIterator<int, int> it2 = t->begin();  
    NodeIterator<int, int> it3 = t->end();    

    EXPECT_EQ({it1==it2}, true);  
    EXPECT_EQ({it1==it3}, false);  

    ++it2;
    EXPECT_EQ({it1==it2}, false);  

    delete_tree(t);
}

TEST(ConstIterator, equalityAndInequality) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 5, 5);

    ConstNodeIterator<int, int> it1 = t->cbegin();  
    ConstNodeIterator<int, int> it2 = t->cbegin();  
    ConstNodeIterator<int, int> it3 = t->cend();    

    EXPECT_EQ({it1==it2}, true);  
    EXPECT_EQ({it1==it3}, false);  

    ++it2;
    EXPECT_EQ({it1==it2}, false);  

    delete_tree(t);
}

TEST(ReverseIterator, equalityAndInequality) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 5, 5);

    NodeIterator<int, int> it1 = t->rbegin();  
    NodeIterator<int, int> it2 = t->rbegin();  
    NodeIterator<int, int> it3 = t->rend();    

    EXPECT_EQ({it1==it2}, true);  
    EXPECT_EQ({it1==it3}, false);  

    ++it2;
    EXPECT_EQ({it1==it2}, false);  

    delete_tree(t);
}

// PRE AND POSTFIX

TEST(ForwardIterator, PrefixAndPostFix) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    NodeIterator<int, int> it = t->begin();  
    NodeIterator<int, int> pre = ++it;  

    EXPECT_EQ(it->data, 20);  
    EXPECT_EQ(pre->data, 20);   

    NodeIterator<int, int> post = it++;
    EXPECT_EQ(it->data, 50);    
    EXPECT_EQ(post->data, 20);  // post has old value

    delete_tree(t);
}

TEST(ConstIterator, PrefixAndPostFix) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    ConstNodeIterator<int, int> it = t->cbegin();  
    ConstNodeIterator<int, int> pre = ++it;  

    EXPECT_EQ(it->data, 20);  
    EXPECT_EQ(pre->data, 20);   

    ConstNodeIterator<int, int> post = it++;
    EXPECT_EQ(it->data, 50);    
    EXPECT_EQ(post->data, 20);  // post has old value

    delete_tree(t);
}

TEST(ReverseIterator, PrefixAndPostFix) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    NodeIterator<int, int> it = t->rbegin();  
    NodeIterator<int, int> pre = ++it;  

    EXPECT_EQ(it->data, 20);  
    EXPECT_EQ(pre->data, 20);   

    NodeIterator<int, int> post = it++;
    EXPECT_EQ(it->data, 10);    
    EXPECT_EQ(post->data, 20);  // post has old value

    delete_tree(t);
}

// SWAP

TEST(ForwardIterator, swap) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    NodeIterator<int, int> it1 = t->begin();  
    NodeIterator<int, int> it2 = t->end();    

    swap(it1, it2);

    EXPECT_EQ(it1, t->end());  
    EXPECT_THROW({it1->data;}, out_of_range);
    
    EXPECT_EQ(it2, t->begin()); 
    EXPECT_EQ(it2->data, 10);
          
    delete_tree(t);
}

TEST(ConstIterator, swap) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    ConstNodeIterator<int, int> it1 = t->cbegin();  
    ConstNodeIterator<int, int> it2 = t->cend();    

    swap(it1, it2);

    EXPECT_EQ(it1, t->cend());  
    EXPECT_THROW({it1->data;}, out_of_range);
    
    EXPECT_EQ(it2, t->cbegin()); 
    EXPECT_EQ(it2->data, 10);
          
    delete_tree(t);
}

TEST(ReverseIterator, swap) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    NodeIterator<int, int> it1 = t->rbegin();  
    NodeIterator<int, int> it2 = t->rend();    

    swap(it1, it2);

    EXPECT_EQ(it1, t->rend());  
    EXPECT_THROW({it1->data;}, out_of_range);
    
    EXPECT_EQ(it2, t->rbegin()); 
    EXPECT_EQ(it2->data, 50);
          
    delete_tree(t);
}


// MODIFY AND INCREMENT

TEST(ForwardIterator, modifyAndIncrement) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    NodeIterator<int, int> it = t->begin();  
    ++it;  
    insert(t, 15, 15);  

    EXPECT_EQ(it->data, 20);  
    insert(t, 30, 30);  
    ++it;  
    EXPECT_EQ(it->data, 30);  

    delete_tree(t);
}

TEST(ConstIterator, modifyAndIncrement) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    ConstNodeIterator<int, int> it = t->cbegin();  
    ++it;  
    insert(t, 15, 15);  

    EXPECT_EQ(it->data, 20);  
    insert(t, 30, 30);  
    ++it;  
    EXPECT_EQ(it->data, 30);  

    delete_tree(t);
}

TEST(ReverseIterator, modifyAndIncrement) {
    Node<int, int>* t = createNode(10, 10);
    insert(t, 20, 20);
    insert(t, 50, 50);

    NodeIterator<int, int> it = t->rbegin();  
    ++it;  
    insert(t, 30, 30);  

    EXPECT_EQ(it->data, 20);  
    insert(t, 15, 15);  
    ++it;  
    EXPECT_EQ(it->data, 15);  

    delete_tree(t);
}