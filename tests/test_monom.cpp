#include <gtest/gtest.h>
#include "../lib_Monom/monom.h"

TEST(TestMonomLib, test_initialize_constructor) {
    ASSERT_NO_THROW(Monom monom1);
    ASSERT_NO_THROW(Monom monom2(3.2, { 1, 0, 3 }));
}

TEST(TestMonomLib, test_constructor_from_string) {
    ASSERT_NO_THROW(Monom monom1("5x^2yz^3"));
    ASSERT_ANY_THROW(Monom monom2("u^3"));
}

TEST(TestMonomLib, test_copy_constructor) {
    Monom monom1(-3, { 2, 5, 3 });
    ASSERT_NO_THROW(Monom monom2(monom1));
}

TEST(TestMonomLib, test_compare_operators) {
    Monom monom1(2, { 0, 1, 3 }), monom2(3.4, {0, 1, 3});
    ASSERT_TRUE(monom1 == monom2);
    ASSERT_FALSE(monom1 != monom2);
    ASSERT_FALSE(monom1 > monom2);

    Monom monom3(2, { 1, 1, 3 }), monom4(2, {0, 0, 4});
    ASSERT_FALSE(monom3 == monom4);
    ASSERT_TRUE(monom3 != monom4);

    ASSERT_FALSE(monom3 < monom2);
}

TEST(TestMonomLib, test_assign_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(5, { 2, 3, 0 });
    ASSERT_NO_THROW(monom1 = monom2);
    ASSERT_NO_THROW(monom1 = monom1);
}

TEST(TestMonomLib, test_add_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(5, { 2, 3, 0 });
    ASSERT_NO_THROW(monom1 + monom2);

    Monom monom3(3, { 1, 1, 1 });
    ASSERT_ANY_THROW(monom1 + monom3);
}

TEST(TestMonomLib, test_sub_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(5, { 2, 3, 0 });
    ASSERT_NO_THROW(monom1 - monom2);

    Monom monom3(3, { 1, 1, 1 });
    ASSERT_ANY_THROW(monom1 - monom3);
    ASSERT_NO_THROW(monom1 = -monom2);
}

TEST(TestMonomLib, test_mul_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(-5, { 1, 0, 4 });  // -5xz^4 * 3x^2y^3 = -15x^3y^3z^4
    ASSERT_NO_THROW(monom1 * monom2);
    ASSERT_NO_THROW(monom1 * 3);
}

TEST(TestMonomLib, test_div_operator) {
    Monom monom1(8, { 2, 3, 1 }), monom2(4, { 1, 0, 1 });  // 8x^2y^3z / 4xz = 2xy^3
    Monom res = monom1 / monom2;
    ASSERT_NO_THROW(monom1 / monom2);
    ASSERT_NO_THROW(monom1 / 2);
}

TEST(TestMonomLib, test_calculate) {
    Monom monom(-2, { 1, 2, 1 });
    ASSERT_EQ(monom.calculate({2, 2, 4}), -64.0);  // -2xy^2z (2, 2, 4) = -64
}
