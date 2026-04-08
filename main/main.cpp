// Copyright 2024 Marina Usova

#include <iostream>
//#define EASY_EXAMPLE
//#define CHECK_CIRCLES
//#define EXPRESSION_APPLICATION
//#define SKIPLIST
//#define SEARCH_TREE_SORT
//#define HEAP_SORT
//#define PRIORITY_QUEUE
#define DICT_UNION
#ifdef EASY_EXAMPLE

#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE


#ifdef CHECK_CIRCLES
#include "algorithms.h"

void print_result(Type result) {
    if (result == Type::intersect)
        std::cout << "intersect" << std::endl;
    else if (result == Type::touch)
        std::cout << "touch" << std::endl;
    else if (result == Type::inside)
        std::cout << "inside" << std::endl;
    else if (result == Type::not_touch)
        std::cout << "not_touch" << std::endl;
}

int main() {
    Circle circle1(0, 0, 2), circle2(0, 0, 3);
    Type result = check_circles(circle1, circle2);
    print_result(result);

    Circle circle3(-1, -1, 1), circle4(2, 2, 1);
    result = check_circles(circle3, circle4);
    print_result(result);

    Circle circle5(0, 0, 1), circle6(0, 2, 1);
    result = check_circles(circle5, circle6);
    print_result(result);

    Circle circle7(0, 0, 1), circle8(0, 1, 1);
    result = check_circles(circle7, circle8);
    print_result(result);

    return 0;
}

#endif


#ifdef EXPRESSION_APPLICATION

#include "expression.h"
#include "tvector.h"

void print_variables(Expression expression) {
    TVector<Lexem> variables = expression.get_variables();

    int max_lenght = 51;
    std::string str = "";
    for (int i = 0; i < variables.size(); i++) {
        Lexem var = variables[i];

        if (var._value == DBL_MAX)
            str += var._name + " = ?";
        else
            str += var._name + " = " + std::to_string(var._value);

        if (i != variables.size() - 1) str += ", ";
    }

    for (int i = str.size(); i < max_lenght; i++)
        str += " ";
    std::cout << str << "|" << std::endl;
}

void print_expressions(TVector<Expression> expressions) {

    std::cout << "+-------------------------------------------------------------------------------------------------------------+" << std::endl;
    std::cout << "| ID | EXPRESSION                                         |VARIABLES VALUES                                   |" << std::endl;
    std::cout << "+-------------------------------------------------------------------------------------------------------------+" << std::endl;
    int max_lenght = 52;

    for (int i = 0; i < expressions.size(); i++) {
        std::string expr = expressions[i].toString();
        std::cout << "| " << i + 1 << "  |" << expr;

        for (int j = expr.size(); j < max_lenght; j++)
            std::cout << " ";
        std::cout << "|";

        print_variables(expressions[i]);
    }
    std::cout << "+-------------------------------------------------------------------------------------------------------------+" << std::endl;
}

void print_main_menu(TVector<Expression> expressions) {
    if (!expressions.is_empty())
        print_expressions(expressions);

    std::cout << "MainMenu:" << std::endl;
    std::cout << "1) Create expression" << std::endl;
    std::cout << "2) Delete expression" << std::endl;
    std::cout << "3) Set Variables" << std::endl;
    std::cout << "4) Calculate" << std::endl;
    std::cout << "5) Exit" << std::endl;
}

int choose_action(int count, std::string enter) {
    if (count == 1) return 1;

    int action;
    while (true) {
        std::cout << enter;
        std::cin >> action;

        if (action <= 0 || action > count)
            std::cout << "Incorrect enter" << std::endl;
        else return action;
    }
}

Expression create_expression() {
    std::string expression_str;

    std::cout << "Enter expression: ";
    std::cin.ignore();
    std::getline(std::cin, expression_str);
    Expression expression(expression_str);

    return expression;
}

void set_variables_for_expression(Expression& expression) {
    TVector<Lexem> variables = expression.get_variables();

    std::cout << "Enter variables: " << std::endl;
    for (int i = 0; i < variables.size(); i++) {
        double value;
        std::cout << variables[i]._name << " = ";
        std::cin >> value;
        expression.set_variables(variables[i]._name, value);
    }
}

int main() {
    TVector<Expression> expressions;

    int action, id;
    while (true) {
        print_main_menu(expressions);
        action = choose_action(5, "Choose action: ");
        system("cls");

        switch (action) {
        case 1:
            try {
                expressions.push_back(create_expression());
                system("cls");
            }
            catch (const std::exception& ex) {
                std::cerr << ex.what() << std::endl;
            }
            break;
        case 2:
            if (!expressions.is_empty()) {
                print_expressions(expressions);
                id = choose_action(expressions.size(), "Enter expression's id: ");
                expressions.erase(expressions.begin() + id - 1);
                system("cls");
            }
            else std::cout << "No expression" << std::endl;
            break;
        case 3:
            if (!expressions.is_empty()) {
                print_expressions(expressions);
                id = choose_action(expressions.size(), "Enter expression's id: ");
                set_variables_for_expression(expressions[id - 1]);
                system("cls");
            }
            else std::cout << "No expression" << std::endl;
            break;
        case 4:
            if (!expressions.is_empty()) {
                print_expressions(expressions);
                id = choose_action(expressions.size(), "Enter expression's id: ");
                try {
                    system("cls");
                    std::cout << expressions[id - 1].toString() << " = " <<
                        expressions[id - 1].calculate() << std::endl;
                }
                catch (const std::exception& ex) {
                    std::cerr << ex.what() << std::endl;
                }
            }
            else std::cout << "No expression" << std::endl;
            break;
        default:
            return 0;
            break;
        }
    }

    return 0;
}

#endif // EXPRESSION_APPLICATION

#ifdef SKIPLIST

#include "skiplist.h"
#include "polynom.h"

int main() {
    SkipList<int, int> list;
    list.insert(4, 1);
    list.insert(7, 15);
    list.insert(24, 4);
    list.insert(2, 8);
    list.insert(1, 9);

    list.print();

    return 0;
}

#endif // SKIPLIST

#ifdef SEARCH_TREE_SORT

#include "bstree.h"
#include "tvector.h"

int main() {
    TVector<int> vec({9, 18, 5, 20, 16, 8, 7, 3, 11});
    BSTree<int, int> tree;
    for (int i = 0; i < vec.size(); i++)
        tree.insert(vec[i], vec[i]);

    tree.print();
    return 0;
}

#endif // SEARCH_TREE_SORT

#ifdef HEAP_SORT
#include "heap.h"

int main() {
    Heap<int> heap;
    heap.push(5);
    heap.push(7);
    heap.push(82);
    heap.push(4);
    heap.push(43);
    heap.push(2);
    heap.push(-6);
    heap.push(20);

    for (int i = 0; i < 8; i++)
        std::cout << heap.pop() << " ";

    return 0;
}

#endif // HEAP_SORT

#ifdef PRIORITY_QUEUE
#define elem 7

#include "priorityqueue.h"
#include <cstdlib>
#include <ctime>

int main() {
    PriotityQueue<int> queue;
    srand(time(0));

    for (int i = 0; i < 10; i++) {
        int priority = 1 + rand() % 5;
        int value = 1 + rand() % 100;

        std::cout << "added " << priority << ": " << value << std::endl;
        queue.push(priority, value, i + 1);
    }
    
    for (int i = 0; i < elem; i++)
        std::cout << queue.pop() << std::endl;

    return 0;
}
#endif // PRIORITY_QUEUE

#ifdef DICT_UNION

#include "hashtable.h"

int main() {
    HashTable<int> table(30);

    TVector<std::pair<std::string, int>> dict1(3), dict2(3);
    dict1[0] = std::pair<std::string, int>("table", 1349);
    dict1[1] = std::pair<std::string, int>("hash", 1985);
    dict1[2] = std::pair<std::string, int>("list", 4372);

    dict2[0] = std::pair<std::string, int>("massive", 4312);
    dict2[1] = std::pair<std::string, int>("list", 4372);
    dict2[2] = std::pair<std::string, int>("hash", 4317);

    for (int i = 0; i < 3; i++) {
        table.insert(dict1[i].first, dict1[i].second);
    }
    for (int i = 0; i < 3; i++) {
        try {
            table.insert(dict2[i].first, dict2[i].second);
        } catch(...) {}
    }

    std::cout << table;
    return 0;
}

#endif // DICT_UNION


