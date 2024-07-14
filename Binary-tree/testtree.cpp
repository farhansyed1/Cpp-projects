#include "bintree.h"
#include <gtest/gtest.h>

// To compile: g++ -o testtree.exe testtree.cpp bintree.cpp -lgtest -lgtest_main -pthread
// Running valgrind: valgrind --leak-check=full --show-leak-kinds=all ./testtree.exe

using namespace std;

// EMPTY TREE

TEST(EmptyTreeTest, insert) {
    Node *t = nullptr;
    insert(t,1,10);
    EXPECT_EQ(t->key, 1);
    EXPECT_EQ(t->data, 10);
    EXPECT_EQ(t->left, nullptr);
    EXPECT_EQ(t->right, nullptr);

    delete_tree(t);
}

TEST(EmptyTreeTest, outOfRangeError) {
    Node *t = nullptr;
    EXPECT_THROW(remove(t, 1), out_of_range);
    EXPECT_THROW(find(t, 1), out_of_range);
    EXPECT_THROW(edit(t, 1), out_of_range);

    delete_tree(t);
}

TEST(EmptyTreeTest, deleteTree) {
    Node *t = nullptr;
    delete_tree(t);
    EXPECT_EQ(t, nullptr);

    delete_tree(t);
}

TEST(EmptyTreeTest, heightAndSize) {
    Node *t = nullptr;
    EXPECT_EQ(max_height(t), 0);
    EXPECT_EQ(min_height(t), 0);
    EXPECT_EQ(size(t), 0);

    delete_tree(t);
}

TEST(EmptyTreeTest, balanced) {
    Node *t = nullptr;
    EXPECT_EQ(is_balanced(t), true);
    
    delete_tree(t);
}

// CORRECTNESS WITH SIZE 1

TEST(CorrectnessSizeOne, insert) {
    Node *t = createNode(1,2);
    insert(t,2,3);
    EXPECT_EQ(t->right->key, 2);
    EXPECT_EQ(t->right->data, 3);
    EXPECT_EQ(t->left, nullptr);
    EXPECT_EQ(size(t), 2);
    EXPECT_EQ(is_balanced(t), true);

    delete_tree(t);
}

TEST(CorrectnessSizeOne, remove) {
    Node *t = createNode(1,2);
    remove(t,1);
    EXPECT_EQ(t, nullptr);

    delete_tree(t);
}

TEST(CorrectnessSizeOne, find) {
    Node *t = createNode(1,2);
    EXPECT_EQ(find(t,1), 2);

    delete_tree(t);
}

TEST(CorrectnessSizeOne, edit) {
    Node *t = createNode(1,2);
    EXPECT_EQ(t->data, 2);

    double &p = edit(t,1);
    p = 5;

    EXPECT_EQ(t->data, 5);

    delete_tree(t);
}

TEST(CorrectnessSizeOne, deleteTree) {
    Node *t = createNode(1,2);
    delete_tree(t);
    EXPECT_EQ(t, nullptr);
}

TEST(CorrectnessSizeOne, heightAndSize) {
    Node *t = createNode(1,2);
    EXPECT_EQ(max_height(t), 1);
    EXPECT_EQ(min_height(t), 1);
    EXPECT_EQ(size(t), 1);
    EXPECT_EQ(is_balanced(t), true);

    delete_tree(t);
}


// CORRECTNESS SIZE > 1

TEST(CorrectnessSizeGreaterThanOne, insertAndRemove) {
    Node *t = createNode(1,2);
    insert(t,2,3);
    insert(t,5,4);
    insert(t,5,10); // duplicate key

    remove(t,1);

    EXPECT_EQ(t->key, 2);
    EXPECT_EQ(t->data, 3);

    EXPECT_EQ(t->left, nullptr);
    EXPECT_EQ(t->right->key, 5);
    EXPECT_EQ(t->right->data, 10);

    EXPECT_EQ(size(t), 2);
    EXPECT_EQ(is_balanced(t), true);

    delete_tree(t);
}

TEST(CorrectnessSizeGreaterThanOne, findAndHeight) {
    Node *t = createNode(10,2);

    insert(t,20,3);
    insert(t,9,1);
    insert(t,7,6);
    insert(t,8,8);

    EXPECT_EQ(find(t,8), 8);
    EXPECT_EQ(size(t), 5);
    EXPECT_EQ(max_height(t), 4);
    EXPECT_EQ(min_height(t), 2);
    EXPECT_EQ(is_balanced(t), false);

    delete_tree(t);
}

TEST(CorrectnessSizeGreaterThanOne, deleteTree) {
    Node *t = createNode(10,2);

    insert(t,20,3);
    insert(t,9,1);
    insert(t,7,6);
    insert(t,8,8);

    delete_tree(t);
    EXPECT_EQ(t, nullptr);
}

TEST(CorrectnessSizeGreaterThanOne, findRemoveFindDelete) {
    Node *t = createNode(1,2);
    insert(t,2,3);
    insert(t,5,4);
    insert(t,5,10); 

    EXPECT_EQ(find(t,5), 10);

    remove(t,5);

    EXPECT_THROW(find(t, 5), out_of_range);
    delete_tree(t);
    EXPECT_THROW(find(t, 1), out_of_range);
    EXPECT_THROW(find(t, 2), out_of_range);
    EXPECT_THROW(find(t, 5), out_of_range);

    insert(t,2,3);
    insert(t,5,4);
    EXPECT_EQ(find(t,2), 3);
    EXPECT_EQ(find(t,5), 4);

    delete_tree(t);
}

// ERROR SIZE > 1

TEST(ThrowErrorSizeGreaterThanOne, remove) {
    Node *t = createNode(10,2);

    insert(t,20,3);
    insert(t,9,1);
    insert(t,7,6);
    insert(t,8,8);

    EXPECT_THROW(remove(t, 1), out_of_range);
    EXPECT_THROW(find(t, 1), out_of_range);
    EXPECT_THROW(edit(t, 1), out_of_range);

    EXPECT_EQ(find(t, 9), 1);
    remove(t,9);
    EXPECT_THROW(remove(t, 9), out_of_range);

    delete_tree(t);
}
