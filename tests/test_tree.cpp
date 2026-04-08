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
    Tree<int, int> tree;
    int mass[10] = { 2, 5, 12, -4, 22, 6, 1, 0, 3, 34 };
    for (int i = 0; i < 10; i++)
        tree.insert(mass[i], mass[i]);

    tree.erase(1);
    ASSERT_EQ(tree.find(1), nullptr);

    ASSERT_ANY_THROW(tree.erase(1));

    // insert after erase
    tree.insert(1, 1);
    ASSERT_EQ(*tree.find(1), 1);
}

TEST(TestTreeLib, test_clear) {
    Tree<int, int> tree;
    for (int i = 0; i < 5; i++)
        tree.insert(i, i);

    tree.clear();
    ASSERT_TRUE(tree.is_empty());
}

//TEST(TestTreeLib, test_print) {
//    Tree<int, int> tree;
//    for (int i = 0; i < 7; i++)
//        tree.insert(i, i);
//
//    tree.print_tree();
//    system("pause");
//}