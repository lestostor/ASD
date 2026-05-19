#include <gtest/gtest.h>
#include "../lib_AVLTree/avltree.h"

TEST(TestAVLTreeLib, test_constructor) {
    AVLTree<int, int> tree1;
    ASSERT_TRUE(tree1.is_empty());

    AVLTree<int, int> tree2(new AVLNode<int, int> (3, 4));
    ASSERT_FALSE(tree2.is_empty());
}

TEST(TestAVLTreeLib, test_insert_and_find) {
    AVLTree<int, int> tree;
    int mass[9] = { 2, 5, 12, 4, 7, 9, 3, 11, 10};  // RR(12), RL(9), LR(3), LL(10)
    for (int i = 0; i < 9; i++)
        tree.insert(mass[i], mass[i]);

    AVLNode<int, int>* root = tree.root();
    ASSERT_EQ(root->_data.first, 5);
    ASSERT_EQ(root->_left->_data.first, 3);
    ASSERT_EQ(root->_right->_data.first, 9);
    ASSERT_EQ(root->_left->_left->_data.first, 2);
    ASSERT_EQ(root->_left->_right->_data.first, 4);
    ASSERT_EQ(root->_right->_left->_data.first, 7);
    ASSERT_EQ(root->_right->_right->_data.first, 11);
    ASSERT_EQ(root->_right->_right->_left->_data.first, 10);
    ASSERT_EQ(root->_right->_right->_right->_data.first, 12);

    ASSERT_EQ(*tree.find(10), 10);
    ASSERT_EQ(tree.find(15), nullptr);

    ASSERT_ANY_THROW(tree.insert(2, 5));
}

TEST(TestAVLTreeLib, test_erase) {
    AVLTree<int, int> tree;
    int mass[9] = { 2, 5, 12, 4, 7, 9, 3, 11, 10 };
    for (int i = 0; i < 9; i++)
        tree.insert(mass[i], mass[i]);

    AVLNode<int, int>* root = tree.root();
    tree.erase(7);  // RL
    ASSERT_EQ(root->_right->_data.first, 10);
    ASSERT_EQ(root->_right->_left->_data.first, 9);
    ASSERT_EQ(root->_right->_right->_data.first, 11);
    ASSERT_EQ(root->_right->_right->_right->_data.first, 12);
    tree.erase(5);  // balanced
    ASSERT_EQ(root->_data.first, 4);
    tree.erase(9);  // RR
    ASSERT_EQ(root->_right->_data.first, 11);
    ASSERT_EQ(root->_right->_left->_data.first, 10);
    ASSERT_EQ(root->_right->_right->_data.first, 12);
    root = tree.root();
    ASSERT_ANY_THROW(tree.erase(-4));
}

TEST(TestAVLTreeLib, test_erase_2) {
    AVLTree<int, int> tree;
    int mass[13] = { 40, 20, 60, 15, 25, 50, 70, 5, 45, 55, 65, 80, 75 };

    for (int i = 0; i < 13; i++)
        tree.insert(mass[i], mass[i]);

    tree.erase(25);

    AVLNode<int, int>* root = tree.root();
    ASSERT_EQ(root->_data.first, 60);
    ASSERT_EQ(root->_left->_data.first, 40);
    ASSERT_EQ(root->_right->_data.first, 70);
    ASSERT_EQ(root->_left->_left->_data.first, 15);
    ASSERT_EQ(root->_left->_right->_data.first, 50);
    ASSERT_EQ(root->_left->_left->_left->_data.first, 5);
    ASSERT_EQ(root->_left->_left->_right->_data.first, 20);
    ASSERT_EQ(root->_left->_right->_left->_data.first, 45);
    ASSERT_EQ(root->_left->_right->_right->_data.first, 55);
    ASSERT_EQ(root->_right->_left->_data.first, 65);
    ASSERT_EQ(root->_right->_right->_data.first, 80);
    ASSERT_EQ(root->_right->_right->_left->_data.first, 75);
    ASSERT_EQ(tree.find(25), nullptr);
}
