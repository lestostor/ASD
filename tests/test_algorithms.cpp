#include <gtest/gtest.h>
#include "algorithms.h"

TEST(TestAlgorithmsLib, test_check_circles_if_inside) {
    Circle circle1(0, 0, 2), circle2(0, 0, 3);
    Type result = check_circles(circle1, circle2);
    ASSERT_EQ(result, Type::inside);
}

TEST(TestAlgorithmsLib, test_check_circles_if_not_touch) {
    Circle circle1(-1, -1, 1), circle2(2, 2, 1);
    Type result = check_circles(circle1, circle2);
    ASSERT_EQ(result, Type::not_touch);
}

TEST(TestAlgorithmsLib, test_check_circles_if_touch) {
    Circle circle1(0, 0, 1), circle2(0, 2, 1);
    Type result = check_circles(circle1, circle2);
    ASSERT_EQ(result, Type::touch);
}

TEST(TestAlgorithmsLib, test_check_circles_if_intersect) {
    Circle circle1(0, 0, 1), circle2(0, 1, 1);
    Type result = check_circles(circle1, circle2);
    ASSERT_EQ(result, Type::intersect);
}

TEST(TestAlgorithmsLib, test_check_spheres_if_inside) {
    Sphere sphere1(0, 0, 0, 2), sphere2(0, 0, 0, 4);
    Type result = check_spheres(sphere1, sphere2);
    ASSERT_EQ(result, Type::inside);
}

TEST(TestAlgorithmsLib, test_check_spheres_if_not_touch) {
    Sphere sphere1(-10, 0, 0, 2), sphere2(10, 10, 10, 4);
    Type result = check_spheres(sphere1, sphere2);
    ASSERT_EQ(result, Type::not_touch);
}

TEST(TestAlgorithmsLib, test_check_spheres_if_touch) {
    Sphere sphere1(0, 0, 0, 1), sphere2(0, 0, 2, 1);
    Type result = check_spheres(sphere1, sphere2);
    ASSERT_EQ(result, Type::touch);
}

TEST(TestAlgorithmsLib, test_check_spheres_if_intersect) {
    Sphere sphere1(0, 0, 0, 2), sphere2(0, 0, 1, 2);
    Type result = check_spheres(sphere1, sphere2);
    ASSERT_EQ(result, Type::intersect);
}

TEST(TestAlgorithmsLib, test_find_local_min_matrix_3x3) {
    Matrix<int> matrix(3, 3);
    matrix[0] = MathVector({ 3, 1, 2 });
    matrix[1] = MathVector({ 5, 8, 4 });
    matrix[2] = MathVector({ 7, 6, 9 });

    bool result = false;
    int min = find_local_min(matrix);
    if (min == 1 || min == 6)
        result = true;
    ASSERT_TRUE(result);
}

TEST(TestAlgorithmsLib, test_find_local_min_matrix_4x4) {
    Matrix<int> matrix(4, 4);
    matrix[0] = MathVector({ 11, 15, 10, 9 });
    matrix[1] = MathVector({ 6, 16, 3, 8 });
    matrix[2] = MathVector({ 7, 4, 2, 13 });
    matrix[3] = MathVector({ 14, 12, 1, 5 });

    bool result = false;
    int min = find_local_min(matrix);
    if (min == 1 || min == 6)
        result = true;
    ASSERT_TRUE(result);
}

TEST(TestAlgorithmsLib, test_find_local_min_matrix_5x5) {
    Matrix<int> matrix(5, 5);
    matrix[0] = MathVector({ 20, 15, 4, 9, 25 });
    matrix[1] = MathVector({ 6, 21, 3, 8, 17 });
    matrix[2] = MathVector({ 18, 10, 19, 13, 7});
    matrix[3] = MathVector({ 14, 12, 22, 5, 2 });
    matrix[4] = MathVector({ 11, 16, 1, 24, 20 });

    bool result = false;
    int min = find_local_min(matrix);
    if (min == 1 || min == 2 || min == 3 || min == 6 || min == 10 || min == 11)
        result = true;
    ASSERT_TRUE(result);
}