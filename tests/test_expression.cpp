#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

TEST(TestExpressionLib, test_isvalid_No1) {
    ASSERT_TRUE(Parser::is_valid("15+ 23"));
}

TEST(TestExpressionLib, test_is_valid_No2) {
    ASSERT_TRUE(Parser::is_valid("15 + 23 *4"));
}

TEST(TestExpressionLib, test_is_valid_No3) {
    ASSERT_TRUE(Parser::is_valid("(15+ 23) * 2"));
}

TEST(TestExpressionLib, test_is_valid_No4) {
    ASSERT_TRUE(Parser::is_valid("34 +(15+ 23) * 2"));
}

TEST(TestExpressionLib, test_is_valid_No5) {
    ASSERT_TRUE(Parser::is_valid("x+ y"));
}

TEST(TestExpressionLib, test_is_valid_No6) {
    ASSERT_TRUE(Parser::is_valid("2*x+ y"));
}

TEST(TestExpressionLib, test_is_valid_No7) {
    ASSERT_TRUE(Parser::is_valid("2*x+ (y - 3*z)"));
}

TEST(TestExpressionLib, test_is_valid_No8) {
    ASSERT_TRUE(Parser::is_valid("3 * (15 + |az2 + y| * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_No9) {
    ASSERT_TRUE(Parser::is_valid("3 * (15 + (x + y) * (- 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_operation) {
    ASSERT_FALSE(Parser::is_valid("3 * (15 + (x y) * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_second_operand) {
    ASSERT_FALSE(Parser::is_valid("3 * (15 + (x + y) * (2*x - 7 * y^))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_closed_bracket) {
    ASSERT_FALSE(Parser::is_valid("3 * (15 + (x + y) * (2*x - 7 * y^2)"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_opened_bracket) {
    ASSERT_FALSE(Parser::is_valid("3 * 15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_first_operand) {
    ASSERT_FALSE(Parser::is_valid(" * (15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_operand_after_opened_bracket) {
    ASSERT_FALSE(Parser::is_valid("3 * ( + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_operation_before_opened_bracket) {
    ASSERT_FALSE(Parser::is_valid("3  (15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_extra_operation) {
    ASSERT_FALSE(Parser::is_valid("3 * (15 + (x +-/ y) * (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_is_valid_if_missed_operation_between_brackets) {
    ASSERT_FALSE(Parser::is_valid("3 * (15 + (x + y) (2*x - 7 * y^2))"));
}

TEST(TestExpressionLib, test_parse_No1) {
    std::string expression = "23 * 284 + 1";
    List<Lexem> lexems = Parser::parse(expression);
    List<std::string> expected;
    expected.push_back("23");
    expected.push_back("*");
    expected.push_back("284");
    expected.push_back("+");
    expected.push_back("1");

    List<Lexem>::Iterator lex_it = lexems.begin();
    List<std::string>::Iterator ex_it = expected.begin();
    for (lex_it, ex_it; lex_it != lexems.end(); lex_it++, ex_it++)
        ASSERT_EQ((*lex_it)._name, *ex_it);
}

TEST(TestExpressionLib, test_parse_No2) {
    std::string expression = "3 *tg(x+y)";
    List<Lexem> lexems = Parser::parse(expression);
    List<std::string> expected;
    expected.push_back("3");
    expected.push_back("*");
    expected.push_back("tg");
    expected.push_back("(");
    expected.push_back("x");
    expected.push_back("+");
    expected.push_back("y");
    expected.push_back(")");

    List<Lexem>::Iterator lex_it = lexems.begin();
    List<std::string>::Iterator ex_it = expected.begin();
    for (lex_it, ex_it; lex_it != lexems.end(); lex_it++, ex_it++)
        ASSERT_EQ((*lex_it)._name, *ex_it);
}

TEST(TestExpressionLib, test_parse_No3) {
    std::string expression = "3 ^ x *|45 - 2 * a_1|";
    List<Lexem> lexems = Parser::parse(expression);
    List<std::string> expected;
    expected.push_back("3");
    expected.push_back("^");
    expected.push_back("x");
    expected.push_back("*");
    expected.push_back("|");
    expected.push_back("45");
    expected.push_back("-");
    expected.push_back("2");
    expected.push_back("*");
    expected.push_back("a_1");
    expected.push_back("|");

    List<Lexem>::Iterator lex_it = lexems.begin();
    List<std::string>::Iterator ex_it = expected.begin();
    for (lex_it, ex_it; lex_it != lexems.end(); lex_it++, ex_it++)
        ASSERT_EQ((*lex_it)._name, *ex_it);
}

TEST(TestExpressionLib, test_parse_wrong_expression) {
    ASSERT_ANY_THROW(List<Lexem> lexems = Parser::parse("3  x *4"));
}

TEST(TestExpressionLib, test_constructor_by_string) {
    ASSERT_NO_THROW(Expression expr("(a + b * c) * 5"));
}

TEST(TestExpressionLib, test_constructor_by_list_of_lexems) {
    List<Lexem> lexems = Parser::parse("2 + sin(2*x)");
    ASSERT_NO_THROW(Expression expr(lexems));
}

TEST(TestExpressionLib, test_constructor_with_abs_and_pow) {
    ASSERT_NO_THROW(Expression expr("3 * |-y - x ^ a|"));
}

TEST(TestExpressionLib, test_calculate_constants) {
    Expression expr("3 * (21 -3)");
    ASSERT_EQ(expr.calculate(), 54);
}

TEST(TestExpressionLib, test_calculate_constants_and_variables) {
    Expression expr("3 * x1 / 5");
    expr.set_variables("x1", 20);
    ASSERT_EQ(expr.calculate(), 12);
}

TEST(TestExpressionLib, test_calculate_if_variables_is_not_set) {
    Expression expr("3 * x1 / 5");
    ASSERT_ANY_THROW(expr.calculate());
}

TEST(TestExpressionLib, test_calculate_two_variables) {
    Expression expr("y * x1 ^ 2");
    expr.set_variables("x1", 4);
    expr.set_variables("y", 3);
    ASSERT_EQ(expr.calculate(), 48);
}

TEST(TestExpressionLib, test_calculate_function) {
    Expression expr("- 3 + tg(x)");
    expr.set_variables("x", 0);
    ASSERT_EQ(expr.calculate(), -3);
}

TEST(TestExpressionLib, test_calculate_expression_with_abs) {
    Expression expr("|2 ^ x_q - 50| + a^4");
    expr.set_variables("x_q", 5);
    expr.set_variables("a", 3);
    ASSERT_EQ(expr.calculate(), 99);
}