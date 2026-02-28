#include <gtest/gtest.h>
#include "sortedvectable.h"

TEST(TestSortedVecTableLib, test_constructor) {
    SortedVecTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestSortedVecTableLib, test_insert) {
    SortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(2 * i + 1, 2 * i + 1);
    table.insert(4, 4);

    ASSERT_ANY_THROW(table.insert(3, 5));
}

TEST(TestSortedVecTableLib, test_find) {
    SortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i + 1);
    ASSERT_EQ(*table.find(3), 4);
    ASSERT_EQ(table.find(5), nullptr);
}

TEST(TestSortedVecTableLib, test_erase) {
    SortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i + 1);
    table.erase(3);
    ASSERT_EQ(table.find(3), nullptr);
}