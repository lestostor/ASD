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