#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"

TEST(TestDsuLib, test_constructor) {
    ASSERT_NO_THROW(DSU dsu(5));
}

TEST(TestDsuLib, test_find) {
    DSU dsu(5);
    ASSERT_EQ(dsu.find(3), 3);
}

TEST(TestDsuLib, test_find_wrong_element) {
    DSU dsu(5);
    ASSERT_ANY_THROW(dsu.find(5));
    ASSERT_ANY_THROW(dsu.find(-2));
}

TEST(TestDsuLib, test_unite) {
    DSU dsu1(5), dsu2(5), dsu3(5);
    dsu1.unite(1, 4);
    dsu1.unite(2, 4);
    ASSERT_EQ(dsu1.find(4), 1);

    dsu2.unite(4, 2);
    ASSERT_EQ(dsu2.find(2), 4);

    dsu3.unite(4, 4);
    ASSERT_EQ(dsu3.find(4), 4);
}

TEST(TestDsuLib, test_unite_wrong_elements) {
    DSU dsu(5);
    ASSERT_ANY_THROW(dsu.unite(-1, 4));
    ASSERT_ANY_THROW(dsu.unite(1, 5));
}
