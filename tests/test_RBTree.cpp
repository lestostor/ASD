#include <gtest/gtest.h>
#include "rbtree.h"

TEST(TestRBTreeLib, test_constructor) {
    RBTree<int, int> tree1;
    ASSERT_TRUE(tree1.is_empty());

    RBTree<int, int> tree2(new RBNode<int, int>(3, 4));
    ASSERT_FALSE(tree2.is_empty());
}

TEST(TestRBTreeLib, test_insert_rotates) {
    RBTree<int, int> tree;

    tree.insert(12, 12);
    tree.insert(5, 5);  // R
    tree.insert(20, 20);  // R
    tree.insert(-9, -9);  // R, 5->B, 20->B
    tree.insert(-3, -3);  // LR, -9->B, -3->R
    ASSERT_ANY_THROW(tree.insert(-9, 4));

    RBNode<int, int>* root = tree.root();
    ASSERT_EQ(root->_color, black);
    ASSERT_EQ(root->_left->_color, black);
    ASSERT_EQ(root->_right->_color, black);
    ASSERT_EQ(root->_left->_left->_color, red);
    ASSERT_EQ(root->_left->_right->_color, red);
}

TEST(TestRBTreeLib, check_insert_recolors) {
    RBTree<int, int> tree;
    tree.insert(55, 55);
    tree.insert(33, 33);
    tree.insert(75, 75);
    tree.insert(10, 10);
    tree.insert(61, 61);
    tree.insert(44, 44);
    tree.insert(83, 83);
    tree.insert(5, 5);
    tree.insert(56, 56);
    tree.insert(79, 79);
    tree.insert(65, 65);
    tree.insert(90, 90);
    tree.insert(85, 85);

    RBNode<int, int>* root = tree.root();
    ASSERT_EQ(root->_color, black);  // 55
    ASSERT_EQ(root->_left->_color, black);  // 33
    ASSERT_EQ(root->_left->_left->_color, black);  // 10
    ASSERT_EQ(root->_left->_right->_color, black);  // 44
    ASSERT_EQ(root->_left->_left->_left->_color, red);  // 5
    ASSERT_EQ(root->_right->_color, black);  // 75
    ASSERT_EQ(root->_right->_right->_color, red);  // 83
    ASSERT_EQ(root->_right->_right->_left->_color, black);  // 79
    ASSERT_EQ(root->_right->_right->_right->_color, black);  // 90
    ASSERT_EQ(root->_right->_left->_color, black);  // 61
    ASSERT_EQ(root->_right->_left->_left->_color, red);  // 56
    ASSERT_EQ(root->_right->_left->_right->_color, red);  // 65
    ASSERT_EQ(root->_right->_right->_right->_left->_color, red);  // 85
}
