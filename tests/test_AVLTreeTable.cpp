#include <gtest/gtest.h>
#include "avltreetable.h"

TEST(TestAVLTreeTableLib, test_constructor) {
    AVLTreeTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestAVLTreeTableLib, test_insert_and_find) {
    AVLTreeTable<int, int> table;

    int elements[5] = { 4, 10, -71, 36, 12 };
    for (int i = 0; i < 5; i++)
        table.insert(elements[i], elements[i]);

    table.insert(6, 6);
    ASSERT_EQ(*table.find(6), 6);
    ASSERT_ANY_THROW(table.insert(4, 3));
}

TEST(TestAVLTreeTableLib, test_erase) {
    AVLTreeTable<int, int> table;

    int elements[5] = { 4, 10, -71, 36, 12 };
    for (int i = 0; i < 5; i++)
        table.insert(elements[i], elements[i]);

    table.erase(12);
    ASSERT_EQ(table.find(12), nullptr);

    ASSERT_ANY_THROW(table.erase(12));
}

//TEST(TestAVLTreeTableLib, test_output) {
//    AVLTreeTable<int, int> table;
//
//    int elements[5] = { 4, 10, -71, 36, 12 };
//    for (int i = 0; i < 5; i++)
//        table.insert(elements[i], elements[i]);
//
//    std::cout << table;
//    system("pause");
//}