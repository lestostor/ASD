#include <gtest/gtest.h>
#include "point.h"

TEST(TestPointLib, test_default_construction) {
    ASSERT_NO_THROW (Point point);
}

TEST(TestPointLib, test_initialize_constructor) {
    ASSERT_NO_THROW (Point point(1, -4));
}

TEST(TestPointLib, test_copy_constructor) {
    ASSERT_NO_THROW (Point point1(1, -4), point2(point1));
}

TEST(TestPointLib, test_count_distance) {
    Point point1(1, 0), point2(-1, 0);

    float expected_result = 2;
    float actual_result = point1.distance(point2);

    EXPECT_NEAR(expected_result, actual_result, 0.000000001);
}

TEST(TestPointLib, test_operator_if_equal ) {
    Point point1(1, 0), point2(point1);

    bool expected_result = true, actual_result = (point1 == point2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestPointLib, test_operator_if_not_equal) {
    Point point1(1, 0), point2(-1, 0);

    bool expected_result = false, actual_result = (point1 == point2);

    ASSERT_EQ(expected_result, actual_result);
}