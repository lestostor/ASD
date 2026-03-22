#include <gtest/gtest.h>
#include "sortedtreetable.h"

TEST(TestSortedTreeTableLib, test_constructor) {
    SortedTreeTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestSortedTreeTableLib, test_insert_and_find) {
    SortedTreeTable<int, int> table;

    for (int i = 0; i < 5; i++)
        table.insert(2 * i + 1, 2 * i + 1);

    table.insert(6, 6);
    ASSERT_EQ(*table.find(6), 6);
    ASSERT_ANY_THROW(table.insert(1, 3));

    ASSERT_EQ(table.find(0), nullptr);
}

TEST(TestSortedTreeTableLib, test_erase) {
    SortedTreeTable<int, int> table;

    for (int i = 0; i < 5; i++)
        table.insert(2 * i + 1, 2 * i + 1);

    table.erase(5);
    ASSERT_EQ(table.find(5), nullptr);

    ASSERT_ANY_THROW(table.erase(5));
}

//TEST(TestSortedTreeTableLib, test_output) {
//    SortedTreeTable<int, int> table;
//
//    for (int i = 0; i < 5; i++)
//        table.insert(2 * i + 1, 2 * i + 1);
//
//    std::cout << table;
//    system("pause");
//}