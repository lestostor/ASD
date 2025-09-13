#include <gtest/gtest.h>
#include "point3D.h"

TEST(TestPoint3DLib, test_default_constructor) {
    ASSERT_NO_THROW(Point3D point);
}

TEST(TestPoint3DLib, test_initialize_constructor) {
    ASSERT_NO_THROW(Point3D point(1, 2, 3));
}

TEST(TestPoint3DLib, test_convert_constructor) {
    Point point2d(1, 2);
    ASSERT_NO_THROW(Point3D point(point2d));
}

TEST(TestPoint3DLib, test_copy_constructor) {
    Point3D point1(1, 2, 3);
    ASSERT_NO_THROW(Point3D point2(point1));
}

TEST(TestPoint3DLib, test_count_distance) {
    Point3D point1(1, 0, 0), point2(-1, 0, 0);

    float expected_result = 2;
    float actual_result = point1.distance(point2);

    EXPECT_NEAR(expected_result, actual_result, 0.000000001);
}

TEST(TestPoint3DLib, test_operator_if_equal) {
    Point3D point1(1, 0, 2), point2(point1);

    bool expected_result = true, actual_result = (point1 == point2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestPoint3DLib, test_operator_if_not_equal) {
    Point3D point1(1, 0, 2), point2(-1, 0, 3);

    bool expected_result = false, actual_result = (point1 == point2);

    ASSERT_EQ(expected_result, actual_result);
}