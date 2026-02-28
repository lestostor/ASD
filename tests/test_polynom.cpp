#include <gtest/gtest.h>
#include "polynom.h"

TEST(TestPolynomLib, test_default_constructor) {
    Polynom pol;
    ASSERT_EQ("zero = 0.000000", pol.to_string());
}

TEST(TestPolynomLib, test_convert_constructor) {
    Polynom pol("p", Monom (2, {3, 0, 1}));
    ASSERT_EQ("p = 2.000000x^3z", pol.to_string());
}

TEST(TestPolynomLib, test_constructor_from_string) {
    Polynom pol1("p1", "x^2 + z");
    Polynom pol2("p2", "3y^3 - 4x^2");
    Polynom pol3("p3", "5.2z -10xy^2z^3 - 4");

    ASSERT_EQ("p1 = x^2+z", pol1.to_string());
    ASSERT_EQ("p2 = -4.000000x^2+3.000000y^3", pol2.to_string());
    ASSERT_EQ("p3 = -10.000000xy^2z^3+5.200000z-4.000000", pol3.to_string());
}

TEST(TestPolynomLib, test_add_operator) {
    Polynom p1("p1", "x^2 - 5y^3z + y^2"), p2("p2", "x^2 + z^2");

    ASSERT_EQ((p1 + p2).to_string(), "zero = 2.000000x^2-5.000000y^3z+y^2+z^2");

    Monom monom1("3x^2"), monom2("-x^3"), monom3("4x");
    ASSERT_EQ((p1 + monom1).to_string(), "p1 = 4.000000x^2-5.000000y^3z+y^2");
    ASSERT_EQ((p1 + monom2).to_string(), "p1 = -x^3+x^2-5.000000y^3z+y^2");
    ASSERT_EQ((p1 + monom3).to_string(), "p1 = x^2+4.000000x-5.000000y^3z+y^2");

    p1 += p2;
    ASSERT_EQ(p1.to_string(), "p1 = 2.000000x^2-5.000000y^3z+y^2+z^2");

    p1 += monom1;
    ASSERT_EQ(p1.to_string(), "p1 = 5.000000x^2-5.000000y^3z+y^2+z^2");
}

TEST(TestPolynomLib, test_sub_operator) {
    Polynom p1("p1", "x^2 - 5y^3z + y^2"), p2("p2", "x^2 + z^2");
    p1 -= p2;
    ASSERT_EQ(p1.to_string(), "p1 = -5.000000y^3z+y^2-z^2");
    ASSERT_EQ((-p1).to_string(), "p1 = 5.000000y^3z-y^2+z^2");

    Monom monom1("3x^2"), monom2("-x^3"), monom3("4x");
    ASSERT_EQ((p1 - monom1).to_string(), "p1 = -3.000000x^2-5.000000y^3z+y^2-z^2");
    ASSERT_EQ((p1 - monom2).to_string(),"p1 = x^3-5.000000y^3z+y^2-z^2" );
    ASSERT_EQ((p1 - monom3).to_string(), "p1 = -4.000000x-5.000000y^3z+y^2-z^2");

    p1 -= monom1;
    ASSERT_EQ(p1.to_string(), "p1 = -3.000000x^2-5.000000y^3z+y^2-z^2");
}

TEST(TestPolynomLib, test_mul_operator) {
    Polynom p1("p1", "3y^2 - 4"), p2("p2", "5x^3y + 2z");
    p1 *= p2;
    ASSERT_EQ(p1.to_string(), "p1 = 15.000000x^3y^3-20.000000x^3y+6.000000y^2z-8.000000z");
    p1 *= 4;
    ASSERT_EQ(p1.to_string(), "p1 = 60.000000x^3y^3-80.000000x^3y+24.000000y^2z-32.000000z");

    Monom monom("z^2");
    p2 *= monom;
    ASSERT_EQ(p2.to_string(), "p2 = 5.000000x^3yz^2+2.000000z^3");
}

TEST(TestPolynomLib, test_div_operator) {
    Polynom p("p", "x^2y^2z - 5y^3z + y^2");
    Monom monom("4y");
    p /= monom;
    ASSERT_EQ(p.to_string(), "p = 0.250000x^2yz-1.250000y^2z+0.250000y");
}

TEST(TestPolynomLib, test_calculate) {
    Polynom p("p", "5x^3y + 2z");
    ASSERT_EQ(p.calculate({ 2, 2, 5 }), 90);
}