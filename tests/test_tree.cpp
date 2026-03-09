#include <gtest/gtest.h>
#include "../lib_tree/tree.h"

TEST(TestTreeLib, test_default_constructor) {
    Tree<int, int> tree;
    ASSERT_TRUE(tree.is_empty());
}

TEST(TestTreeLib, test_initialize_constructor) {
    Tree<int, int> tree(new Node<int, int>(3, 4));
    ASSERT_FALSE(tree.is_empty());
}

TEST(TestTreeLib, test_insesrt_and_find) {
    Tree<int, int> tree(new Node<int, int>(1, 1));
    for (int i = 2; i < 5; i++)
        tree.insert(i, i);
    ASSERT_EQ(*tree.find(3), 3);
    ASSERT_EQ(tree.find(5), nullptr);
}

TEST(TestTreeLib, test_erase) {
    Tree<int, int> tree(new Node<int, int>(1, 1));
    for (int i = 2; i < 5; i++)
        tree.insert(i, i);
    
    tree.erase(3);
    ASSERT_EQ(tree.find(3), nullptr);
}