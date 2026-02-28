#include <gtest/gtest.h>
#include "unsortedvectable.h"

TEST(TestUnsortedVecTableLib, test_constructor) {
    UnsortedVecTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestUnsortedVecTableLib, test_insert) {
    UnsortedVecTable<int, int> table;
    table.insert(3, 4);
    ASSERT_FALSE(table.is_empty());

    ASSERT_ANY_THROW(table.insert(3, 5));
}

TEST(TestUnsortedVecTableLib, test_find) {
    UnsortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i + 1);
    ASSERT_EQ(*table.find(3), 4);
    ASSERT_EQ(table.find(5), nullptr);
}

TEST(TestUnsortedVecTableLib, test_erase) {
    UnsortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i + 1);
    table.erase(3);
    ASSERT_EQ(table.find(3), nullptr);
}