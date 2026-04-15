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
    int mass[10] = { 2, 5, 12, -4, 7, 9, 0, 11, 10};  // RR(12), RL(9), LR(0), LL(10)
    for (int i = 0; i < 9; i++)
        tree.insert(mass[i], mass[i]);

    ASSERT_EQ(*tree.find(-4), -4);
    ASSERT_EQ(tree.find(1), nullptr);

    ASSERT_ANY_THROW(tree.insert(2, 5));
}

TEST(TestAVLTreeLib, test_erase) {
    AVLTree<int, int> tree;
    int mass[10] = { 2, 5, 12, -4, 7, 9, 0, 11, 10 };
    for (int i = 0; i < 9; i++)
        tree.insert(mass[i], mass[i]);

    tree.erase(7);  // RL
    ASSERT_EQ(tree.find(7), nullptr);
    tree.erase(5);  // balanced
    ASSERT_EQ(tree.find(5), nullptr);
    tree.erase(-4);  // RR
    ASSERT_EQ(tree.find(-4), nullptr);

    ASSERT_ANY_THROW(tree.erase(-4));
}
