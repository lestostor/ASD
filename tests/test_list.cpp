#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestListLib, test_default_constructor) {
    ASSERT_NO_THROW(List<int> list);
}

TEST(TestListLib, test_is_empty_if_empty) {
    List<int> list;
    ASSERT_TRUE(list.is_empty());
}

TEST(TestListLib, test_push_front) {
    List<int> list;
    list.push_front(5);
    ASSERT_EQ(list.head()->_value, 5);
}

TEST(TestListLib, test_is_empty_if_not_empty) {
    List<int> list;
    list.push_front(5);
    ASSERT_FALSE(list.is_empty());
}

TEST(TestListLib, test_push_back) {
    List<int> list;
    list.push_front(4);
    list.push_back(5);
    ASSERT_EQ(list.tail()->_value, 5);
}

TEST(TestListLib, test_copy_contructor) {
    List<int> list1;
    list1.push_back(5);
    list1.push_back(6);
    list1.push_back(7);
    List<int> list2(list1);
    ASSERT_EQ(list2.head()->_value, 5);
    ASSERT_EQ(list2.tail()->_value, 7);
}

TEST(TestListLib, test_insert_by_node) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.insert(list.head(), 4);
    ASSERT_EQ(list.head()->_next->_value, 4);
}

TEST(TestListLib, test_insert_by_null_node) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    ASSERT_ANY_THROW(list.insert(nullptr, 4));
}

TEST(TestListLib, test_insert_by_position) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.insert(1, 4);
    ASSERT_EQ(list.head()->_next->_value, 4);
}

TEST(TestListLib, test_insert_by_wrong_position) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    ASSERT_ANY_THROW(list.insert(4, 4));
}

TEST(TestListLib, test_insert_by_node_after_tail) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.insert(list.tail(), 4);
    ASSERT_EQ(list.tail()->_value, 4);
}

TEST(TestListLib, test_insert_by_position_at_begining) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.insert(size_t(0), 4);
    ASSERT_EQ(list.head()->_value, 4);
}

TEST(TestListLib, test_insert_by_position_after_tail) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.insert(2, 4);
    ASSERT_EQ(list.tail()->_value, 4);
}

TEST(TestListLib, test_pop_back) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.pop_back();
    ASSERT_EQ(list.head()->_value, 3);
    ASSERT_EQ(list.tail()->_value, 3);
}

TEST(TestListLib, test_pop_back_last_element) {
    List<int> list;
    list.push_back(3);
    list.pop_back();
    ASSERT_TRUE(list.is_empty());
}

TEST(TestListLib, test_pop_back_from_empty_list) {
    List<int> list;
    ASSERT_ANY_THROW(list.pop_back());
}

TEST(TestListLib, test_pop_front) {
    List<int> list;
    list.push_back(3);
    list.push_back(5);
    list.pop_front();
    ASSERT_EQ(list.head()->_value, 5);
    ASSERT_EQ(list.tail()->_value, 5);
}

TEST(TestListLib, test_pop_front_last_element) {
    List<int> list;
    list.push_back(3);
    list.pop_front();
    ASSERT_TRUE(list.is_empty());
}

TEST(TestListLib, test_pop_front_from_empty_list) {
    List<int> list;
    ASSERT_ANY_THROW(list.pop_front());
}

TEST(TestListLib, test_pop_erase_by_node) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.erase(list.head());
    ASSERT_EQ(list.head()->_next->_value, 5);
}

TEST(TestListLib, test_pop_erase_tail_by_node) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.erase(list.head()->_next);
    ASSERT_EQ(list.tail()->_value, 4);
}

TEST(TestListLib, test_erase_by_node_from_empty_list) {
    List<int> list;
    ASSERT_ANY_THROW(list.erase(list.head()));
}

TEST(TestListLib, test_erase_null_node) {
    List<int> list;
    ASSERT_ANY_THROW(list.erase(nullptr));
}

TEST(TestListLib, test_pop_erase_by_position) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.erase(1);
    ASSERT_EQ(list.head()->_next->_value, 5);
}

TEST(TestListLib, test_pop_erase_by_wrong_position) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    ASSERT_ANY_THROW(list.erase(4));
}

TEST(TestListLib, test_erase_by_position_from_empty_list) {
    List<int> list;
    ASSERT_ANY_THROW(list.erase(1));
}

TEST(TestListLib, test_pop_erase_tail_by_position) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.erase(2);
    ASSERT_EQ(list.tail()->_value, 4);
}

TEST(TestListLib, test_pop_erase_head_by_position) {
    List<int> list;
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.erase(size_t(0));
    ASSERT_EQ(list.head()->_value, 4);
}

TEST(TestListLib, test_iterator_in_empty_list) {
    List<int> list;
    List<int>::Iterator it;
    bool enterCycle = false;
    for (it = list.begin(); it != list.end(); it++) {
        enterCycle = true;
    }
    ASSERT_FALSE(enterCycle);
}

TEST(TestListLib, test_iterator_for_read) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    List<int>::Iterator it;
    int i = 0;
    for (it = list.begin(); it != list.end(); it++) {
        ASSERT_EQ(*it, ++i);
    }
}

TEST(TestListLib, test_iterator_for_write) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(0);

    int i = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        *it = ++i;
    }

    i = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        ASSERT_EQ(*it, ++i);
    }
}

TEST(TestListLib, test_push_back_pop_back) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    list.pop_back();
    ASSERT_EQ(list.tail()->_value, 4);
    list.push_back(5);
    ASSERT_EQ(list.tail()->_value, 5);
}

TEST(TestListLib, test_push_front_pop_front) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_front(i + 1);

    list.pop_front();
    ASSERT_EQ(list.head()->_value, 4);
    list.push_front(5);
    ASSERT_EQ(list.head()->_value, 5);
}
