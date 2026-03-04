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

    TVector<int> expected({1, 3, 4, 5, 7, 9});
    for (int i = 0; i < 10; i++) {
        int* elem = table.find(i);
        if (elem)
            ASSERT_EQ(*elem, i);
    }

    ASSERT_ANY_THROW(table.insert(3, 5));
}

TEST(TestSortedVecTableLib, test_find) {
    SortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i + 1, i + 1);
    ASSERT_EQ(*table.find(3), 3);
    ASSERT_EQ(table.find(6), nullptr);
}

TEST(TestSortedVecTableLib, test_erase) {
    SortedVecTable<int, int> table;
    for (int i = 0; i < 5; i++)
        table.insert(i + 1, i + 1);
    table.erase(3);
    ASSERT_EQ(table.find(3), nullptr);

    ASSERT_ANY_THROW(table.erase(3));

    // insert after erase
    table.insert(3, 3);
    TVector<int> expected({ 1, 2, 3, 4, 5});
    for (int i = 0; i < 10; i++) {
        int* elem = table.find(i);
        if (elem)
            ASSERT_EQ(*elem, i);
    }
}