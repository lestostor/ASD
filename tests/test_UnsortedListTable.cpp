#include <gtest/gtest.h>
#include "unsortedlisttable.h"

TEST(TestUnsortedListTableLib, test_constructor) {
    UnsortedListTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestUnsortedListTableLib, test_insert) {
    UnsortedListTable<int, int> table;
    table.insert(3, 4);
    ASSERT_FALSE(table.is_empty());

    ASSERT_ANY_THROW(table.insert(3, 5));
}

TEST(TestUnsortedListTableLib, test_find) {
    UnsortedListTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i + 1);
    ASSERT_EQ(*table.find(3), 4);
    ASSERT_EQ(table.find(5), nullptr);
}

TEST(TestUnsortedListTableLib, test_erase) {
    UnsortedListTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i + 1);
    table.erase(3);
    ASSERT_EQ(table.find(3), nullptr);

    table.insert(3, 4);
    ASSERT_EQ(*table.find(3), 4);
}