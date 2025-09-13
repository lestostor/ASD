#include <gtest/gtest.h>
#include "sphere.h"

TEST(TestSphereLib, test_default_constructor) {
    ASSERT_NO_THROW(Sphere sphere);
}

TEST(TestSphereLib, test_first_initialize_constructor) {
    Point3D centre(1, -2, 0);
    ASSERT_NO_THROW(Sphere sphere(centre, 3));
}

TEST(TestSphereLib,
    test_first_initialize_constructor_with_negative_radius) {
    Point3D centre(1, -2, 0);
    ASSERT_ANY_THROW(Sphere sphere(centre, -3));
}

TEST(TestSphereLib, test_second_initialize_constructor) {
    ASSERT_NO_THROW(Sphere sphere(1, -2, 3, 4));
}

TEST(TestSphereLib,
    test_second_initialize_constructor_with_negative_radius) {
    ASSERT_ANY_THROW(Sphere sphere(1, -2, -3, -4));
}

TEST(TestSphereLib, test_copy_constructor) {
    Sphere sphere1(1, 2, 3, 4);
    ASSERT_NO_THROW(Sphere sphere2(sphere1));
}

TEST(TestSphereLib, test_get_radius) {
    Sphere sphere(1, 2, 3, 4);

    float expected_result = 4, actual_result = sphere.get_radius();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestSphereLib, test_get_centre) {
    Sphere sphere(1, 2, 3, 4);

    Point3D expected_result(1, 2, 3), actual_result = sphere.get_centre();

    ASSERT_EQ(expected_result, actual_result);
}