#include <gtest/gtest.h>
#include "mathvector.h"

TEST(TestMathVectorLib, test_defaut_constructor) {
    ASSERT_NO_THROW(MathVector<int> vector);
}

TEST(TestMathVectorLib, test_initialize_constructor_with_null_start_index) {
    ASSERT_NO_THROW(MathVector<int> vector(3));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_start_index) {
    ASSERT_NO_THROW(MathVector<int> vector(3, 1));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_negative_start_index) {
    ASSERT_ANY_THROW(MathVector<int> vector(3, -1));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_start_index_over_size) {
    ASSERT_ANY_THROW(MathVector<int> vector(3, 3));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_null_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    
    for (int i = 0; i < 5; i++)
        ASSERT_EQ(*(vector.begin() + i), i + 1);
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 2);

    for (int i = 0; i < 5; i++)
        ASSERT_EQ(*(vector.begin() + i), i + 1);
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_negative_start_index) {
    ASSERT_ANY_THROW(MathVector<int> vector({ 1, 2, 3, 4, 5 }, -1));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_start_index_over_size) {
    ASSERT_ANY_THROW(MathVector<int> vector({ 1, 2, 3, 4, 5 }, 6));
}

TEST(TestMathVectorLib, test_copy_constructor) {
    MathVector vector1({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_NO_THROW(MathVector<int> vector2(vector1));
}