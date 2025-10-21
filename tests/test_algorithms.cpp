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