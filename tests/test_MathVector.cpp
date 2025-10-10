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

TEST(TestMathVectorLib, test_copy_constructor) {
    MathVector<int> vector1({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_NO_THROW(MathVector<int> vector2(vector1));
}

TEST(TestMathVectorLib, test_index_operator) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    ASSERT_EQ(vector[2], 3);
}

TEST(TestMathVectorLib, test_index_operator_for_zero_element) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 2);
    int result = vector[1];
    ASSERT_EQ(result, 0);
}

TEST(TestMathVectorLib, test_index_operator_out_of_range) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    ASSERT_NE(vector[5], 5);
}

TEST(TestMathVectorLib, test_index_operator_with_negative_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    ASSERT_NE(vector[-3], 3);
}

TEST(TestMathVectorLib, test_index_operator_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_EQ(vector[2], 2);
}

TEST(TestMathVectorLib, test_index_operator_out_of_range_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_NE(vector[6], 6);
}

TEST(TestMathVectorLib, test_at) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    ASSERT_EQ(vector.at(2), 3);
}

TEST(TestMathVectorLib, test_at_for_zero_element) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 2);
    int result = vector.at(1);
    ASSERT_EQ(result, 0);
}

TEST(TestMathVectorLib, test_at_out_of_range) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    ASSERT_ANY_THROW(vector.at(5));
}

TEST(TestMathVectorLib, test_at_with_negative_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    ASSERT_ANY_THROW(vector.at(-3));
}

TEST(TestMathVectorLib, test_at_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_EQ(vector.at(2), 2);
}

TEST(TestMathVectorLib, test_at_out_of_range_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_ANY_THROW(vector.at(6));
}

TEST(TestMathVectorLib, test_at_with_negative_index_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 1);
    ASSERT_ANY_THROW(vector.at(-1));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_negative_start_index) {
    ASSERT_ANY_THROW(MathVector<int> vector(3, -1));
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_null_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 });
    
    for (int i = 0; i < 5; i++)
        ASSERT_EQ(vector[i], i + 1);
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_start_index) {
    MathVector<int> vector({ 1, 2, 3, 4, 5 }, 1);

    for (int i = 0; i < 5; i++) {
        int element = vector[i];
        ASSERT_EQ(element, i);
    }
}

TEST(TestMathVectorLib, test_initialize_constructor_with_initialize_list_with_negative_start_index) {
    ASSERT_ANY_THROW(MathVector<int> vector({ 1, 2, 3, 4, 5 }, -1));
}

TEST(TestMathVectorLib, test_operator_add_with_assign) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6 }), expected({ 5, 7, 9 });
    vector1 += vector2;

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(vector1[i], expected[i]);
}

TEST(TestMathVectorLib, test_operator_add) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6 }), expected({ 5, 7, 9 }), result;
    result = vector1 + vector2;
    for (int i = 0; i < 3; i++)
        ASSERT_EQ(result[i], expected[i]);
}

TEST(TestMathVectorLib, test_operator_add_if_different_sizes) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6, 7 });
    ASSERT_ANY_THROW(vector1 + vector2);
}

TEST(TestMathVectorLib, test_operator_add_if_different_start_index) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6}, 2);
    ASSERT_ANY_THROW(vector1 + vector2);
}

TEST(TestMathVectorLib, test_operator_add_if_different_start_index_but_equal_sizes) {
    MathVector<int> vector1({ 1, 2, 3, 4 }), vector2({ 4, 5, 6 }, 1), expected({ 1, 6, 8, 10 }), result;
    result = vector1 + vector2;
    ASSERT_EQ(result, expected);
}

TEST(TestMathVectorLib, test_operator_sub_with_assign) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6 }), expected({ 3, 3, 3 });
    vector2 -= vector1;

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(vector2[i], expected[i]);
}

TEST(TestMathVectorLib, test_operator_sub) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6 }), expected({ 3, 3, 3 }), result;
    result = vector2 - vector1;

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(result[i], expected[i]);
}

TEST(TestMathVectorLib, test_operator_sub_if_different_sizes) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6, 7 });
    ASSERT_ANY_THROW(vector1 - vector2);
}

TEST(TestMathVectorLib, test_operator_sub_if_different_start_index) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6 }, 2);
    ASSERT_ANY_THROW(vector1 - vector2);
}

TEST(TestMathVectorLib, test_operator_sub_if_different_start_index_but_equal_sizes) {
    MathVector<int> vector1({ 1, 2, 3, 4 }), vector2({ 4, 5, 6 }, 1), expected({ 1, -2, -2, -2 }), result;
    result = vector1 - vector2;
    ASSERT_EQ(result, expected);
}

TEST(TestMathVectorLib, test_operator_mul_by_number_with_assign) {
    MathVector<int> vector({ 1, 2, 3 }), expected({ 3, 6, 9 });
    vector *= 3;
    for (int i = 0; i < 3; i++)
        ASSERT_EQ(vector[i], expected[i]);
}

TEST(TestMathVectorLib, test_operator_mul_by_number) {
    MathVector<int> vector({ 1, 2, 3 });
    MathVector<int> result;
    result = vector * 3;

    MathVector<int> expected({ 3, 6, 9 });
    for (int i = 0; i < 3; i++)
        ASSERT_EQ(result[i], expected[i]);
}

TEST(TestMathVectorLib, test_operator_mul_by_vector) {
    MathVector<int> vector1({ 1, 1, 2 }), vector2({ 2, 0, 1 });
    int result;
    result = vector1 * vector2;

    ASSERT_EQ(result, 4);
}

TEST(TestMathVectorLib, test_operator_mul_if_different_sizes) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6, 7 });
    ASSERT_ANY_THROW(vector1 * vector2);
}

TEST(TestMathVectorLib, test_operator_mul_if_different_start_index) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 4, 5, 6 }, 2);
    ASSERT_ANY_THROW(vector1 * vector2);
}

TEST(TestMathVectorLib, test_operator_mul_if_different_start_index_but_equal_sizes) {
    MathVector<int> vector1({ 2, 2, 2, 2 }), vector2({ 3, 3, 3 }, 1);
    int result = vector1 * vector2;
    ASSERT_EQ(result, 18);
}

TEST(TestMathVectorLib, test_operator_assign) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2;
    vector2 = vector1;

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(vector2[i], vector1[i]);
}

TEST(TestMathVectorLib, test_operator_compare_if_equal) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2(vector1);
    ASSERT_TRUE(vector1 == vector2);
}

TEST(TestMathVectorLib, test_operator_compare_if_different) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({1, 2, 2});
    ASSERT_FALSE(vector1 == vector2);
}

TEST(TestMathVectorLib, test_operator_second_compare_if_equal) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2(vector1);
    ASSERT_FALSE(vector1 != vector2);
}

TEST(TestMathVectorLib, test_operator_second_compare_if_different) {
    MathVector<int> vector1({ 1, 2, 3 }), vector2({ 1, 2, 2 });
    ASSERT_TRUE(vector1 != vector2);
}