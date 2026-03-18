#include <gtest/gtest.h>
#include "../lib_BSTree/bstree.h"

TEST(TestBSTreeLib, test_default_constructor) {
    BSTree<int, int> tree;
    ASSERT_TRUE(tree.is_empty());
}

TEST(TestBSTreeLib, test_initialize_constructor) {
    BSTree<int, int> tree(new Node<int, int>(3, 4));
    ASSERT_FALSE(tree.is_empty());
}

TEST(TestBSTreeLib, test_insesrt_and_find) {
    BSTree<int, int> tree;
    int mass[10] = { 2, 5, 12, -4, 22, 6, 11, 0, 3, 34 };
    for (int i = 0; i < 10; i++)
        tree.insert(mass[i], mass[i]);

    ASSERT_EQ(*tree.find(3), 3);
    ASSERT_EQ(tree.find(1), nullptr);

    ASSERT_ANY_THROW(tree.insert(3, 5));
}

TEST(TestBSTreeLib, test_erase) {
    BSTree<int, int> tree;
    int mass[10] = { 2, 5, 12, -4, 22, 6, 11, 0, 3, 34 };
    for (int i = 0; i < 10; i++)
        tree.insert(mass[i], mass[i]);

    tree.erase(34);
    ASSERT_EQ(tree.find(34), nullptr);

    tree.erase(-4);
    ASSERT_EQ(tree.find(-4), nullptr);

    tree.erase(2);
    ASSERT_EQ(tree.find(2), nullptr);

    ASSERT_ANY_THROW(tree.erase(2));
}
