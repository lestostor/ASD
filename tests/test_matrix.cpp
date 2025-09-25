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

TEST(TestMatrixLib, test_transpose) {
    Matrix<int> matrix1(2, 2), matrix2;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            matrix1[i][j] = j + 1;
    matrix2 = matrix1.transpose();

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            ASSERT_EQ(matrix2[i][j], matrix1[j][i]);
}