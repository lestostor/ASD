#include <gtest/gtest.h>
#include "circle.h"

TEST(TestCircleLib, test_default_constructor) {
    ASSERT_NO_THROW(Circle circle);
}

TEST(TestCircleLib, test_first_initialize_constructor) {
    Point centre(1, -2);
    ASSERT_NO_THROW(Circle circle(centre, 3));
}

TEST(TestCircleLib,
    test_first_initialize_constructor_with_negative_radius) {
    Point centre(1, -2);
    ASSERT_ANY_THROW(Circle circle(centre, -3));
}

TEST(TestCircleLib, test_second_initialize_constructor) {
    ASSERT_NO_THROW(Circle circle(1, -2, 3));
}

TEST(TestCircleLib,
    test_second_initialize_constructor_with_negative_radius) {
    ASSERT_ANY_THROW(Circle circle(1, -2, -3));
}

TEST(TestCircleLib, test_copy_constructor) {
    Circle circle1(1, 2, 3);
    ASSERT_NO_THROW(Circle circle2(circle1));
}

TEST(TestCircleLib, test_get_radius) {
    Circle circle(1, 2, 3);

    float expected_result = 3, actual_result = circle.get_radius();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestCircleLib, test_get_centre) {
    Circle circle(1, 2, 3);

    Point expected_result(1, 2), actual_result = circle.get_centre();

    ASSERT_EQ(expected_result, actual_result);
}