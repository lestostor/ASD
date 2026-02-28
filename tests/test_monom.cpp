#include <gtest/gtest.h>
#include "../lib_Monom/monom.h"

TEST(TestMonomLib, test_initialize_constructor) {
    Monom monom1, monom2(3.4, { 0, 1, 3 });
    ASSERT_EQ(monom1.to_string(), "0.000000");
    ASSERT_EQ(monom2.to_string(), "3.400000yz^3");
}

TEST(TestMonomLib, test_constructor_from_string) {
    Monom monom1("5x^2yz^3");
    ASSERT_EQ(monom1.to_string(), "5.000000x^2yz^3");
    ASSERT_ANY_THROW(Monom monom2("u^3"));
}

TEST(TestMonomLib, test_copy_constructor) {
    Monom monom1(-3, { 2, 5, 3 }), monom2(monom1);
    ASSERT_EQ(monom1.to_string(), monom2.to_string());
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
    monom1 = monom2;
    ASSERT_EQ(monom1.to_string(), monom2.to_string());

    monom1 = monom1;
    ASSERT_EQ(monom1.to_string(), monom2.to_string());
}

TEST(TestMonomLib, test_add_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(5, { 2, 3, 0 });
    ASSERT_EQ((monom1 + monom2).to_string(), "8.000000x^2y^3");

    Monom monom3(3, { 1, 1, 1 });
    ASSERT_ANY_THROW(monom1 + monom3);
}

TEST(TestMonomLib, test_sub_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(5, { 2, 3, 0 });
    ASSERT_EQ((monom1 - monom2).to_string(), "-2.000000x^2y^3");

    Monom monom3(3, { 1, 1, 1 });
    ASSERT_ANY_THROW(monom1 - monom3);
    monom1 = -monom2;
    ASSERT_EQ(monom1.to_string(), "-5.000000x^2y^3");
}

TEST(TestMonomLib, test_mul_operator) {
    Monom monom1(3, { 2, 3, 0 }), monom2(-5, { 1, 0, 4 });
    ASSERT_EQ((monom1 * monom2).to_string(), "-15.000000x^3y^3z^4");
    ASSERT_EQ((monom1 * 3).to_string(), "9.000000x^2y^3");
}

TEST(TestMonomLib, test_div_operator) {
    Monom monom1(8, { 2, 3, 1 }), monom2(4, { 1, 0, 1 });
    ASSERT_EQ((monom1 / monom2).to_string(), "2.000000xy^3");
    ASSERT_EQ((monom1 / 2).to_string(), "4.000000x^2y^3z");
}

TEST(TestMonomLib, test_calculate) {
    Monom monom(-2, { 1, 2, 1 });
    ASSERT_EQ(monom.calculate({2, 2, 4}), -64);
}
