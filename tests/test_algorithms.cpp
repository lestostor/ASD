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

TEST(TestAlgorithmsLib, test_check_brackets_No6) {
    ASSERT_FALSE(check_brackets("(] ()"));
}

TEST(TestAlgorithmsLib, test_math_expression_No1) {
    ASSERT_NO_THROW(read_math_expression("15+ 23"));
}

TEST(TestAlgorithmsLib, test_math_expression_No2) {
    ASSERT_NO_THROW(read_math_expression("15 + 23 *4"));
}

TEST(TestAlgorithmsLib, test_math_expression_No3) {
    ASSERT_NO_THROW(read_math_expression("(15+ 23) * 2"));
}

TEST(TestAlgorithmsLib, test_math_expression_No4) {
    ASSERT_NO_THROW(read_math_expression("34 +(15+ 23) * 2"));
}

TEST(TestAlgorithmsLib, test_math_expression_No5) {
    ASSERT_NO_THROW(read_math_expression("x+ y"));
}

TEST(TestAlgorithmsLib, test_math_expression_No6) {
    ASSERT_NO_THROW(read_math_expression("2*x+ y"));
}

TEST(TestAlgorithmsLib, test_math_expression_No7) {
    ASSERT_NO_THROW(read_math_expression("2*x+ (y - 3*z)"));
}

TEST(TestAlgorithmsLib, test_math_expression_No8) {
    ASSERT_NO_THROW(read_math_expression("3 * (15 + (x + y) * (2*x - 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_math_expression_No9) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x y) * (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operation was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No10) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x + y) * (2*x - 7 * y^))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operand was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No11) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x + y) * (2*x - 7 * y^2)");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Closed bracket was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No12) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * 15 + (x + y) * (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Opened bracket was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No13) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x + y) * (2x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operation was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No14) {
    std::string error_msg = "";
    try {
        read_math_expression(" * (15 + (x + y) * (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operand was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No15) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * ( + (x + y) * (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operand was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No16) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x + y) * (2*x  7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operation was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No17) {
    std::string error_msg = "";
    try {
        read_math_expression("3  (15 + (x + y) * (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operation was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No18) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x +-/ y) * (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Extra operation");
}

TEST(TestAlgorithmsLib, test_math_expression_No19) {
    std::string error_msg = "";
    try {
        read_math_expression("3 * (15 + (x + y) (2*x - 7 * y^2))");
    }
    catch (std::exception& ex) {
        error_msg = ex.what();
    }
    ASSERT_EQ(error_msg, "Operation was missed");
}

TEST(TestAlgorithmsLib, test_math_expression_No20) {
    ASSERT_NO_THROW(read_math_expression("3 * (15 + (x + y) * (- 7 * y^2))"));
}

TEST(TestAlgorithmsLib, test_is_looped_if_looped) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    Node<int>* node = list.head()->_next->_next;
    list.tail()->_next = node;
    ASSERT_TRUE(is_looped_1(list));
    ASSERT_TRUE(is_looped_2(list));
    list.tail()->_next = nullptr;
}

TEST(TestAlgorithmsLib, test_is_looped_if_looped_from_begin) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    list.tail()->_next = list.head();
    ASSERT_TRUE(is_looped_1(list));
    ASSERT_TRUE(is_looped_2(list));
    list.tail()->_next = nullptr;
}

TEST(TestAlgorithmsLib, test_is_looped_if_not_looped) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);
    ASSERT_FALSE(is_looped_1(list));
    ASSERT_FALSE(is_looped_2(list));
}

TEST(TestAlgorithmsLib, test_is_looped_if_one_element) {
    List<int> list;
    list.push_back(1);
    ASSERT_FALSE(is_looped_1(list));
    ASSERT_FALSE(is_looped_2(list));
}

TEST(TestAlgorithmsLib, test_is_looped_if_empty) {
    List<int> list;
    ASSERT_FALSE(is_looped_1(list));
    ASSERT_FALSE(is_looped_2(list));
}

TEST(TestAlgorithmsLib, test_find_loop_if_looped) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);

    Node<int>* node = list.head()->_next->_next;
    list.tail()->_next = node;

    ASSERT_EQ(node, find_loop(list));
    //list.tail()->_next = nullptr;
    list.tail()->_next = list.head();
    ASSERT_EQ(list.head(), find_loop(list));
    list.tail()->_next = nullptr;
}

TEST(TestAlgorithmsLib, test_find_loop_if_not_looped) {
    List<int> list;
    for (int i = 0; i < 5; i++)
        list.push_back(i + 1);
    ASSERT_EQ(nullptr, find_loop(list));
}
