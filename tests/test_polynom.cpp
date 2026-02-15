#include <gtest/gtest.h>
#include "polynom.h"

TEST(TestPolynomLib, test_default_constructor) {
    ASSERT_NO_THROW(Polynom pol);
}

TEST(TestPolynomLib, test_convert_constructor) {
    ASSERT_NO_THROW(Polynom pol("p", Monom (2, {3, 0, 1})));
}

TEST(TestPolynomLib, test_constructor_from_string) {
    ASSERT_NO_THROW(Polynom pol1("p1", "x^2 + z"));
    ASSERT_NO_THROW(Polynom pol2("p2", "3y^3 - 4x^2"));
    ASSERT_NO_THROW(Polynom pol3("p3", "-10xy^2z^3 + 5.2z - 4"));
}

TEST(TestPolynomLib, test_add_operator) {
    Polynom p1("p1", "x^2 - 5y^3z + y^2"), p2("p2", "x^2 + z^2");

    ASSERT_NO_THROW(p1 + p2);

    Monom monom1("3x^2"), monom2("-x^3"), monom3("4x");
    ASSERT_NO_THROW(p1 + monom1);
    ASSERT_NO_THROW(p1 + monom2);
    ASSERT_NO_THROW(p1 + monom3);

    ASSERT_NO_THROW(p1 += p2);
    ASSERT_NO_THROW(p1 += monom1);
}

TEST(TestPolynomLib, test_sub_operator) {
    Polynom p1("p1", "x^2 - 5y^3z + y^2"), p2("p2", "x^2 + z^2");
    ASSERT_NO_THROW(p1 -= p2);
    ASSERT_NO_THROW(-p1);

    Monom monom1("3x^2"), monom2("-x^3"), monom3("4x");
    ASSERT_NO_THROW(p1 - monom1);
    ASSERT_NO_THROW(p1 - monom2);
    ASSERT_NO_THROW(p1 - monom3);
    ASSERT_NO_THROW(p1 -= monom1);
}

TEST(TestPolynomLib, test_mul_operator) {
    Polynom p1("p1", "3y^2 - 4"), p2("p2", "5x^3y + 2z");

    ASSERT_NO_THROW(p1 *= p2);  //15x^3y^3 - 20x^3y + 6y^2z - 8z
    ASSERT_NO_THROW(p1 *= 4);

    Monom monom("z^2");
    ASSERT_NO_THROW(p1 *= monom);
}

TEST(TestPolynomLib, test_div_operator) {
    Polynom p1("p", "x^2y^2z - 5y^3z + y^2"), p2(p1);
    Monom monom("4y");
    ASSERT_NO_THROW(p1 /= monom);
    ASSERT_NO_THROW(p2 /= monom);
}

TEST(TestPolynomLib, test_calculate) {
    Polynom p("p", "5x^3y + 2z");
    ASSERT_EQ(p.calculate({ 2, 2, 5 }), 90);
}