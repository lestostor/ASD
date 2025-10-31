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

TEST(TestAlgorithmsLib, test_check_brackets_No1) {
    ASSERT_TRUE(check_brackets("() ()"));
}

TEST(TestAlgorithmsLib, test_check_brackets_No2) {
    ASSERT_TRUE(check_brackets("[(()())({})]"));
}

TEST(TestAlgorithmsLib, test_check_brackets_No3) {
    ASSERT_FALSE(check_brackets("(()()"));
}

TEST(TestAlgorithmsLib, test_check_brackets_No4) {
    ASSERT_FALSE(check_brackets("())(())"));
}

TEST(TestAlgorithmsLib, test_check_brackets_No5) {
    ASSERT_FALSE(check_brackets("((()()(())}"));
}

TEST(TestAlgorithmsLib, test_math_expression_No1) {
    ASSERT_TRUE(check_math_expression("15+ 23"));
}

TEST(TestAlgorithmsLib, test_math_expression_No2) {
    ASSERT_TRUE(check_math_expression("15 + 23 *4"));
}

TEST(TestAlgorithmsLib, test_math_expression_No3) {
    ASSERT_TRUE(check_math_expression("(15+ 23) * 2"));
}

TEST(TestAlgorithmsLib, test_math_expression_No4) {
    ASSERT_TRUE(check_math_expression("34 +(15+ 23) * 2"));
}

TEST(TestAlgorithmsLib, test_math_expression_No5) {
    ASSERT_TRUE(check_math_expression("x+ y"));
}

TEST(TestAlgorithmsLib, test_math_expression_No6) {
    ASSERT_TRUE(check_math_expression("2*x+ y"));
}

TEST(TestAlgorithmsLib, test_math_expression_No7) {
    ASSERT_TRUE(check_math_expression("2*x+ (y - 3*z)"));
}

TEST(TestAlgorithmsLib, test_math_expression_No8) {
    ASSERT_TRUE(check_math_expression("3 * (15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No9) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No10) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x + y) * (2*x - 7 * y^))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No11) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x + y) * (2*x - 7 * y^2)"));
}

TEST(TestAlgorithmsLib, test_math_expression_No12) {
    ASSERT_FALSE(check_math_expression("3 * 15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No13) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x + y) * (2x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No14) {
    ASSERT_FALSE(check_math_expression(" * (15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No15) {
    ASSERT_FALSE(check_math_expression("3 * ( + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No16) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x + y) * (2*x  7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No17) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x + y) * (2*x - 7 * y2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No18) {
    ASSERT_FALSE(check_math_expression("3  (15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No19) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x +-/ y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No20) {
    ASSERT_FALSE(check_math_expression("3 * (15 + (x + y) (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No21) {
    ASSERT_TRUE(check_math_expression("3 * (15 + (x + y) * (- 7 * y^2))"));
}
