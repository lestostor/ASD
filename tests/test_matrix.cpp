#include <gtest/gtest.h>
#include "matrix.h"

TEST(TestMatrixLib, test_default_constructor) {
    ASSERT_NO_THROW(Matrix<int> matrix);
}

TEST(TestMatrixLib, test_initialize_constructor) {
    ASSERT_NO_THROW(Matrix<int> matrix(3, 4));
}

TEST(TestMatrixLib, test_copy_constructor) {
    ASSERT_NO_THROW(Matrix<int> matrix1(3, 4), matrix2(matrix1));
}

TEST(TestMatrixLib, test_operator_assign) {
    Matrix<int> matrix1(3, 4), matrix2;
    matrix2 = matrix1;

    ASSERT_EQ(matrix2.get_lines(), 3);
    ASSERT_EQ(matrix2.get_columns(), 4);
}

TEST(TestMatrixLib, test_operator_index) {
    Matrix<int> matrix(2, 2);
    ASSERT_EQ(matrix[0], MathVector<int>(2));
}

TEST(TestMatrixLib, test_transpose) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            matrix1[i][j] = j + 1;
            matrix2[i][j] = i + 1;
        }
    matrix1.transpose();

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            ASSERT_EQ(matrix2[i][j], matrix1[i][j]);
}

TEST(TestMatrixLib, test_operator_add) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2), result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 2;
        }
    result = matrix1 + matrix2;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            ASSERT_EQ(result[i][j], 3);
}

TEST(TestMatrixLib, test_operator_add_if_different_sizes) {
    Matrix<int> matrix1(2, 2), matrix2(2, 3), result;
    ASSERT_ANY_THROW(result = matrix1 + matrix2);
}

TEST(TestMatrixLib, test_operator_sub) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2), result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 2;
        }
    result = matrix1 - matrix2;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            ASSERT_EQ(result[i][j], -1);
}

TEST(TestMatrixLib, test_operator_sub_if_different_sizes) {
    Matrix<int> matrix1(2, 2), matrix2(2, 3), result;
    ASSERT_ANY_THROW(result = matrix1 - matrix2);
}

TEST(TestMatrixLib, test_operator_mul_by_number) {
    Matrix<int> matrix(2, 2), result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) 
            matrix[i][j] = 2;
    result = matrix * 4;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            ASSERT_EQ(result[i][j], 8);
}

TEST(TestMatrixLib, test_operator_mul_by_vector) {
    Matrix<int> matrix(2, 2);
    MathVector<int> vector({ 1, 2 }), result, expected({ 5, 11 });
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            matrix[i][j] = i * 2 + j + 1;
    result = matrix * vector;

    for (int i = 0; i < 2; i++)
        ASSERT_EQ(result[i], expected[i]);
}

TEST(TestMatrixLib, test_operator_mul_by_matrix) {
    Matrix<int> matrix1(2, 2), matrix2(2, 3), result, expected(2, 3);
    matrix1[0] = MathVector<int>({ 1, 2 });
    matrix1[1] = MathVector<int>({ 2, 1 });
    matrix2[0] = MathVector<int>({ 1, 1, 2 });
    matrix2[1] = MathVector<int>({ 2, 1, 1 });
    expected[0] = MathVector<int>({ 5, 3, 4 });
    expected[1] = MathVector<int>({ 4, 3, 5 });

    result = matrix1 * matrix2;
    for (int i = 0; i < 2; i++)
        EXPECT_EQ(result[i], expected[i]);
}

TEST(TestMatrixLib, test_operator_compare_if_different_sizes) {
    Matrix<int> matrix1(2, 3), matrix2(3, 2);
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixLib, test_operator_compare_if_equal_sizes) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1, 2 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 2, 1 });
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST(TestMatrixLib, test_operator_compare_if_equal) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1, 1 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix2[1] = MathVector<int>({ 1, 1 });
    ASSERT_TRUE(matrix1 == matrix2);
}

TEST(TestMatrixLib, test_operator_compare_itself) {
    Matrix<int> matrix1(2, 2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1, 1 });
    ASSERT_TRUE(matrix1 == matrix1);
}

TEST(TestMatrixLib, test_operator_second_compare_if_different_sizes) {
    Matrix<int> matrix1(2, 3), matrix2(3, 2);
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST(TestMatrixLib, test_operator_second_compare_if_equal_sizes) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1, 2 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 2, 1 });
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST(TestMatrixLib, test_operator_second_compare_if_equal) {
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1, 1 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix2[1] = MathVector<int>({ 1, 1 });
    ASSERT_FALSE(matrix1 != matrix2);
}

TEST(TestMatrixLib, test_operator_second_compare_itself) {
    Matrix<int> matrix1(2, 2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1, 1 });
    ASSERT_FALSE(matrix1 != matrix1);
}

TEST(TestMatrixLib, test_at) {
    Matrix<int> matrix(2, 2);
    ASSERT_EQ(matrix.at(0), MathVector<int>(2));
}

TEST(TestMatrixLib, test_at_out_of_range) {
    Matrix<int> matrix(2, 2);
    ASSERT_ANY_THROW(matrix.at(2));
}

TEST(TestMatrixLib, test_at_with_negative_index) {
    Matrix<int> matrix(2, 2);
    ASSERT_ANY_THROW(matrix.at(-2));
}
