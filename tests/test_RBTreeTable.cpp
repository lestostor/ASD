#include <gtest/gtest.h>
#include "rbtreetable.h"

TEST(TestRBTreeTableLib, test_constructor) {
    RBTreeTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestRBTreeTableLib, test_insert_and_find) {
    RBTreeTable<int, int> table;

    int elements[5] = { 4, 10, -71, 36, 12 };
    for (int i = 0; i < 5; i++)
        table.insert(elements[i], elements[i]);

    table.insert(6, 6);
    ASSERT_EQ(*table.find(6), 6);
    ASSERT_ANY_THROW(table.insert(4, 3));
}

//TEST(TestRBTreeTableLib, test_output) {
//    RBTreeTable<int, int> table;
//
//    int elements[5] = { 4, 10, -71, 36, 12 };
//    for (int i = 0; i < 5; i++)
//        table.insert(elements[i], elements[i]);
//
//    std::cout << table;
//    system("pause");
//}