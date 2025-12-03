#include <gtest/gtest.h>
#include "../lib_DoubleList/doublelist.h"

TEST(TestDoubleListLib, test_default_constructor) {
    ASSERT_NO_THROW(DoubleList<int> list);
}

TEST(TestDoubleListLib, test_push_front) {
    DoubleList<int> list;
    list.push_front(2);
    list.push_front(1);
    ASSERT_FALSE(list.is_empty());
}

TEST(TestDoubleListLib, test_push_back) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT_FALSE(list.is_empty());
}

TEST(TestDoubleListLib, test_copy_constructor) {
    DoubleList<int> list1;
    list1.push_back(3);
    list1.push_back(4);
    DoubleList<int> list2(list1);
    ASSERT_EQ(list2.head()->_value, 3);
    ASSERT_EQ(list2.tail()->_value, 4);
}

TEST(TestDoubleListLib, test_insert_by_node) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(list.head(), 2);
    ASSERT_EQ(list.head()->_next->_value, 2);
}

TEST(TestDoubleListLib, test_insert_by_null_node) {
    DoubleList<int> list;
    list.push_back(3);
    ASSERT_ANY_THROW(list.insert(nullptr, 3));
}

TEST(TestDoubleListLib, test_insert_by_node_in_empty_list) {
    DoubleList<int> list;
    ASSERT_ANY_THROW(list.insert(list.head(), 3));
}

TEST(TestDoubleListLib, test_insert_by_position) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);
    ASSERT_EQ(list.head()->_next->_value, 2);
}

TEST(TestDoubleListLib, test_insert_by_wrong_position) {
    DoubleList<int> list;
    list.push_back(3);
    ASSERT_ANY_THROW(list.insert(2, 3));
}

TEST(TestDoubleListLib, test_insert_by_position_in_empty_list) {
    DoubleList<int> list;
    ASSERT_ANY_THROW(list.insert(1, 3));
}

TEST(TestDoubleListLib, test_pop_front) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);
    
    list.pop_front();
    ASSERT_EQ(list.head()->_value, 2);
}

TEST(TestDoubleListLib, test_pop_front_last_element) {
    DoubleList<int> list;
    list.push_back(1);

    list.pop_front();
    ASSERT_TRUE(list.is_empty());
}

TEST(TestDoubleListLib, test_pop_back) {
    DoubleList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.pop_back();
    ASSERT_EQ(list.head()->_value, 1);
}

TEST(TestDoubleListLib, test_pop_back_last_element) {
    DoubleList<int> list;
    list.push_back(1);

    list.pop_back();
    ASSERT_TRUE(list.is_empty());
}

TEST(TestDoubleListLib, test_erase_by_node) {
    DoubleList<int> list;
    for (int i = 0; i < 3; i++)
        list.push_back(i + 1);

    list.erase(list.head());
    ASSERT_EQ(list.head()->_next->_value, 3);
}

TEST(TestDoubleListLib, test_erase_by_null_node) {
    DoubleList<int> list;
    list.push_back(1);

    ASSERT_ANY_THROW(list.erase(nullptr));
}

TEST(TestDoubleListLib, test_erase_by_node_in_empty_list) {
    DoubleList<int> list;
    ASSERT_ANY_THROW(list.erase(list.head()));
}

TEST(TestDoubleListLib, test_erase_by_position) {
    DoubleList<int> list;
    for (int i = 0; i < 3; i++)
        list.push_back(i + 1);

    list.erase(1);
    ASSERT_EQ(list.head()->_next->_value, 3);
}

TEST(TestDoubleListLib, test_erase_by_wrong_position) {
    DoubleList<int> list;
    list.push_back(1);

    ASSERT_ANY_THROW(list.erase(2));
}

TEST(TestDoubleListLib, test_erase_by_position_in_empty_list) {
    DoubleList<int> list;
    ASSERT_ANY_THROW(list.erase(1));
}

TEST(TestDoubleListLib, test_iterator_in_empty_list) {
    DoubleList<int> list;
    DoubleList<int>::Iterator it;
    bool enterCycle = false;
    for (it = list.begin(); it != list.end(); it++) {
        enterCycle = true;
    }
    ASSERT_FALSE(enterCycle);
}

TEST(TestDoubleListLib, test_iterator_for_read) {
    DoubleList<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    DoubleList<int>::Iterator it = list.rbegin();
    int i = 5;
    for (it; it != list.rend(); it--) {
        ASSERT_EQ(*it, i--);
    }
}


TEST(TestDoubleListLib, test_iterator_for_write) {
    DoubleList<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(0);

    DoubleList<int>::Iterator it = list.begin();
    for (it; it != list.tail(); it++);

    int i = 5;
    while (true) {
        *it = i;
        ASSERT_EQ(*it, i--);
        if (it == list.begin()) break;
        --it;
    }
}

TEST(TestDoubleListLib, test_iterator_for_operator_sub_and_assign) {
    DoubleList<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    DoubleList<int>::Iterator it = list.begin();
    for (int i = 0; i < 3; i++) it++;

    it -= 3;
    ASSERT_EQ(*it, 1);
}
