#include <gtest/gtest.h>
#include "unsortedtreetable.h"

TEST(TestUnsortedTreeTableVec, test_constructor) {
    UnsortedTreeTable<int, int> table;
    ASSERT_TRUE(table.is_empty());
}

TEST(TestUnsortedTreeTableVec, test_insert_and_find) {
    UnsortedTreeTable<int, int> table;
    table.insert(3, 4);
    ASSERT_FALSE(table.is_empty());

    ASSERT_ANY_THROW(table.insert(3, 5));
}

TEST(TestUnsortedTreeTableVec, test_find) {
    UnsortedTreeTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i);
    ASSERT_EQ(*table.find(3), 3);
    ASSERT_EQ(table.find(5), nullptr);
}

TEST(TestUnsortedTreeTableVec, test_erase) {
    UnsortedTreeTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i, i);
    table.erase(3);
    ASSERT_EQ(table.find(3), nullptr);

    table.insert(3, 3);
    ASSERT_EQ(*table.find(3), 3);
}