#include <gtest/gtest.h>
#include "stack.h"

TEST(TestStackLib, test_defualt_constructor) {
    Stack<int> stack;
}

TEST(TestStackLib, test_initialize_constructor) {
    ASSERT_NO_THROW(Stack<int> stack(5));
}

TEST(TestStackLib, test_initialize_constructor_with_negative_size) {
    ASSERT_ANY_THROW(Stack<int> stack(-5));
}

TEST(TestStackLib, test_copy_constructor) {
    Stack<int> stack1(3);
    ASSERT_NO_THROW(Stack<int> stack2(stack1));
}

TEST(TestStackLib, test_is_empty_if_empty) {
    Stack<int> stack(5);
    ASSERT_TRUE(stack.is_empty());
}

TEST(TestStackLib, test_push_and_is_empty_if_not) {
    Stack<int> stack(5);
    stack.push(3);
    ASSERT_FALSE(stack.is_empty());
}

TEST(TestStackLib, test_push_if_full) {
    Stack<int> stack(5);
    for (int i = 0; i < 5; i++)
        stack.push(3);
    ASSERT_ANY_THROW(stack.push(3));
}

TEST(TestStackLib, test_is_full_if_not) {
    Stack<int> stack(5);
    stack.push(3);
    ASSERT_FALSE(stack.is_full());
}

TEST(TestStackLib, test_is_full_if_full) {
    Stack<int> stack(5);
    for (int i = 0; i < 5; i++)
        stack.push(3);
    ASSERT_TRUE(stack.is_full());
}

TEST(TestStackLib, test_top) {
    Stack<int> stack(5);
    for (int i = 0; i < 4; i++)
        stack.push(i + 1);
    ASSERT_TRUE(stack.top(), 4);;
}

TEST(TestStackLib, test_top_if_empty) {
    Stack<int> stack(5);
    ASSERT_ANY_THROW(stack.top());
}

TEST(TestStackLib, test_pop) {
    Stack<int> stack(5);
    for (int i = 0; i < 4; i++)
        stack.push(i + 1);
    stack.pop();
    ASSERT_TRUE(stack.top(), 3);;
}

TEST(TestStackLib, test_pop_if_empty) {
    Stack<int> stack(5);
    ASSERT_ANY_THROW(stack.pop());
}

TEST(TestStackLib, test_clear) {
    Stack<int> stack(5);
    for (int i = 0; i < 4; i++)
        stack.push(i + 1);
    stack.clear();
    ASSERT_TRUE(stack.is_empty());
}

TEST(TestStackLib, test_push_after_pop) {
    Stack<int> stack(5);
    for (int i = 0; i < 3; i++)
        stack.push(i + 1);
    stack.pop();
    stack.push(4);
    ASSERT_EQ(stack.top(), 4);
}

TEST(TestStackLib, test_is_empty_after_pushes_and_pops) {
    Stack<int> stack(5);
    for (int i = 0; i < 4; i++)
        stack.push(i + 1);
    for (int i = 0; i < 4; i++)
        stack.pop();
    ASSERT_TRUE(stack.is_empty());
}

