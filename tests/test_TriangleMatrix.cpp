#include <gtest/gtest.h>
#include "trianglematrix.h"

TEST(TestTriangleMatrixLib, test_default_constructor) {
    ASSERT_NO_THROW(TriangleMatrix<int> matrix);
}

TEST(TestTriangleMatrixLib, test_initialize_constructor) {
    ASSERT_NO_THROW(TriangleMatrix<int> matrix(5));
}

TEST(TestTriangleMatrixLib, test_copy_constructor) {
    TriangleMatrix<int> matrix1(2);
    ASSERT_NO_THROW(TriangleMatrix<int> matrix2(matrix1));
}

TEST(TestTriangleMatrixLib, test_operator_assign) {
    TriangleMatrix<int> matrix1(3), matrix2;
    matrix2 = matrix1;

    ASSERT_EQ(matrix2.size(), 3);
}

TEST(TestTriangleMatrixLib, test_operator_index) {
    TriangleMatrix<int> matrix(2);
    ASSERT_EQ(matrix[0], MathVector<int>(2));
}