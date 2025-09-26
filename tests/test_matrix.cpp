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

    ASSERT_EQ(matrix2.size(), 3);
}

TEST(TestMatrixLib, test_operator_index) {
    Matrix<int> matrix(2, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            matrix[i][j] = j + 1;

    
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

TEST(TestMatrixLib, test_operator_mul) {
    Matrix<int> matrix(2, 2), result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) 
            matrix[i][j] = 2;
    result = matrix * 4;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            ASSERT_EQ(result[i][j], 8);
}
