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

TEST(TestTriangleMatrixLib, test_operator_add) {
    TriangleMatrix<int> matrix1(3), matrix2(3), result;

    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 2;
        }

    result = matrix1 + matrix2;
    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
            ASSERT_EQ(result[i][j], 3);
}

TEST(TestTriangleMatrixLib, test_operator_add_if_different_sizes) {
    TriangleMatrix<int> matrix1(3), matrix2(2), result;

    ASSERT_ANY_THROW(matrix1 + matrix2);
}


TEST(TestTriangleMatrixLib, test_operator_sub) {
    TriangleMatrix<int> matrix1(3), matrix2(3), result;

    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 2;
        }

    result = matrix2 - matrix1;
    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
            ASSERT_EQ(result[i][j], 1);
}

TEST(TestTriangleMatrixLib, test_operator_sub_if_different_sizes) {
    TriangleMatrix<int> matrix1(3), matrix2(2), result;

    ASSERT_ANY_THROW(matrix2 - matrix1);
}

TEST(TestTriangleMatrixLib, test_operator_mul_by_number) {
    TriangleMatrix<int> matrix(3), result;

    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++) {
            matrix[i][j] = 2;
        }

    result = matrix * 3;
    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
            ASSERT_EQ(result[i][j], 6);
}

TEST(TestTriangleMatrixLib, test_operator_mul_by_vector) {
    TriangleMatrix<int> matrix(3);
    MathVector<int> vector({ 1, 2, 3 }), result, expected({ 12,10,6 });

    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++) {
            matrix[i][j] = 2;
        }

    result = matrix * vector;
    for (int i = 0; i < 3; i++)
        EXPECT_EQ(result[i], expected[i]);
}

TEST(TestTriangleMatrixLib, test_operator_mul_by_vector_if_different_sizes) {
    TriangleMatrix<int> matrix(3);
    MathVector<int> vector({ 1, 2, 3 , 4});
    ASSERT_ANY_THROW(matrix * vector);
}

TEST(TestTriangleMatrixLib, test_operator_mul_by_vector_if_different_sizes_with_start_index) {
    TriangleMatrix<int> matrix(3);
    MathVector<int> vector({ 1, 2, 3 }, 1);
    ASSERT_ANY_THROW(matrix * vector);
}

TEST(TestTriangleMatrixLib, test_operator_mul_by_triangle_matrix) {
    TriangleMatrix<int> matrix1(3), matrix2(3), result, expected(3);

    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++) {
            matrix1[i][j] = 1;
            matrix2[i][j] = 2;
        }
    expected[0] = MathVector<int>({ 2, 4, 6 });
    expected[1] = MathVector<int>({ 2, 4,}, 1);
    expected[2] = MathVector<int>({ 2 }, 2);

    result = matrix2 * matrix1;
    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
            ASSERT_EQ(result[i][j], expected[i][j]);
}

TEST(TestTriangleMatrixLib, test_operator_compare_if_different_sizes) {
    TriangleMatrix<int> matrix1(3), matrix2(2);
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST(TestTriangleMatrixLib, test_operator_compare_if_equal_sizes) {
    TriangleMatrix<int> matrix1(2), matrix2(2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 2 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1 });
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST(TestTriangleMatrixLib, test_operator_compare_if_equal) {
    TriangleMatrix<int> matrix1(2), matrix2(2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix2[1] = MathVector<int>({ 1 });
    ASSERT_TRUE(matrix1 == matrix2);
}

TEST(TestTriangleMatrixLib, test_operator_compare_itself) {
    TriangleMatrix<int> matrix(2);
    matrix[0] = MathVector<int>({ 1, 1 });
    matrix[1] = MathVector<int>({ 1 });
    ASSERT_TRUE(matrix == matrix);
}

TEST(TestTriangleMatrixLib, test_operator_second_compare_if_different_sizes) {
    TriangleMatrix<int> matrix1(3), matrix2(2);
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST(TestTriangleMatrixLib, test_operator_second_compare_if_equal_sizes) {
    TriangleMatrix<int> matrix1(2), matrix2(2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 2 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1 });
    ASSERT_TRUE(matrix1 != matrix2);
}

TEST(TestTriangleMatrixLib, test_operator_second_compare_if_equal) {
    TriangleMatrix<int> matrix1( 2), matrix2(2);
    matrix1[0] = MathVector<int>({ 1, 1 });
    matrix1[1] = MathVector<int>({ 1 });
    matrix2[0] = MathVector<int>({ 1, 1 });
    matrix2[1] = MathVector<int>({ 1 });
    ASSERT_FALSE(matrix1 != matrix2);
}

TEST(TestTriangleMatrixLib, test_operator_second_compare_itself) {
    TriangleMatrix<int> matrix(2);
    matrix[0] = MathVector<int>({ 1, 1 });
    matrix[1] = MathVector<int>({ 1 });
    ASSERT_FALSE(matrix != matrix);
}

TEST(TestTriangleMatrixLib, test_at) {
    TriangleMatrix<int> matrix(2);
    ASSERT_EQ(matrix.at(1), MathVector<int>(1));
}

TEST(TestTriangleMatrixLib, test_at_out_of_range) {
    TriangleMatrix<int> matrix(2);
    ASSERT_ANY_THROW(matrix.at(2));
}

TEST(TestTriangleMatrixLib, test_at_with_negative_index) {
    TriangleMatrix<int> matrix(2);
    ASSERT_ANY_THROW(matrix.at(-2));
}
