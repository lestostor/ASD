#include <gtest/gtest.h>
#include "queue.h"

TEST(TestQueueLib, test_default_constructor) {
    ASSERT_NO_THROW(Queue<int> queue);
}

TEST(TestQueueLib, test_initialize_constructor) {
    ASSERT_NO_THROW(Queue<int> queue(5));
}

TEST(TestQueueLib, test_initialize_constructor_with_negative_size) {
    ASSERT_ANY_THROW(Queue<int> queue(-5));
}

TEST(TestQueueLib, test_copy_constructor) {
    Queue<int> queue1(4);
    ASSERT_NO_THROW(Queue<int> queue2(queue1));
}

TEST(TestQueueLib, test_is_empty_if_empty) {
    Queue<int> queue(5);
    ASSERT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, test_push_and_is_empty_if_not_empty) {
    Queue<int> queue(5);
    queue.push(4);
    ASSERT_FALSE(queue.is_empty());
}

TEST(TestQueueLib, test_is_full_if_empty) {
    Queue<int> queue(5);
    ASSERT_FALSE(queue.is_full());
}

TEST(TestQueueLib, test_is_full_if_full) {
    Queue<int> queue(5);
    for (int i = 0; i < 5; i++)
        queue.push(3);
    ASSERT_TRUE(queue.is_full());
}

TEST(TestQueueLib, test_push_in_full_queue) {
    Queue<int> queue(5);
    for (int i = 0; i < 5; i++)
        queue.push(3);
    ASSERT_ANY_THROW(queue.push(3));
}

TEST(TestQueueLib, test_pop) {
    Queue<int> queue(5);
    queue.push(3);
    queue.pop();
    ASSERT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, test_pop_in_empty_queue) {
    Queue<int> queue(5);
    ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueueLib, test_head) {
    Queue<int> queue(5);
    queue.push(3);
    queue.push(4);
    ASSERT_EQ(queue.head(), 3);
}

TEST(TestQueueLib, test_tail) {
    Queue<int> queue(5);
    queue.push(3);
    queue.push(4);
    ASSERT_EQ(queue.tail(), 4);
}

TEST(TestQueueLib, test_push_after_pop) {
    Queue<int> queue(5);
    for (int i = 0; i < 3; i++)
        queue.push(3);
    queue.pop();
    queue.push(4);
    ASSERT_EQ(queue.tail(), 4);
}

TEST(TestQueueLib, test_push_in_begin_after_pop) {
    Queue<int> queue(5);
    for (int i = 0; i < 5; i++)
        queue.push(i + 1);
    queue.pop();
    queue.pop();
    queue.push(6);
    ASSERT_EQ(queue.tail(), 6);
}

TEST(TestQueueLib, test_clear) {
    Queue<int> queue(5);
    for (int i = 0; i < 5; i++)
        queue.push(i + 1);
    queue.clear();
    ASSERT_TRUE(queue.is_empty());
}

TEST(TestQueueLib, test_copy_after_pushes_and_pops) {
    Queue<int> queue1(5);
    for (int i = 0; i < 5; i++)
        queue1.push(i + 1);
    queue1.pop();
    queue1.pop();
    queue1.push(6);
    ASSERT_NO_THROW(Queue<int> queue2(queue1));
}
