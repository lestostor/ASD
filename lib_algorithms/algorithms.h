#ifndef ALGORITHMS_ALGORITHMS_H
#define ALGORITHMS_ALGORITHMS_H

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include <string>

enum Type { intersect, touch, inside, not_touch };

Type check_circles(Circle, Circle);

Type check_spheres(Sphere, Sphere);

bool check_brackets(std::string);

std::string read_number(std::string, int);
std::string read_variable(std::string, int);

bool is_operation(char);
bool is_digit(char);
bool is_letter(char);
bool is_opened_bracket(char);
bool is_closed_bracket(char);
bool is_function(std::string);

void read_math_expression(std::string);

template <class T>
bool is_looped_1(List<T>& list) {
    if (list.is_empty()) return false;

    List<T>::Iterator bunny = list.begin(),
        turtle = list.begin();
    bool result = false;
    while (bunny != nullptr && turtle != nullptr) {
        bunny++;
        if (bunny == nullptr) break;
        bunny++;
        turtle++;
        if (bunny == turtle) {
            result = true;
            break;
        }
    }
    return result;
}

template <class T>
bool is_looped_2(List<T>& list) {
    if (list.is_empty()) return false;

    bool result = false;
    Node<T>* cur = list.head(), *prev = nullptr, *next_node;
    while (cur != nullptr) {;
        if (cur->_next == list.head()) {
            result = true;
            break;
        }
        next_node = cur->_next;
        cur->_next = prev;
        prev = cur;
        cur = next_node;
    }

    cur = prev;
    prev = nullptr;
    while (cur != nullptr) {
        next_node = cur->_next;
        cur->_next = prev;
        prev = cur;
        cur = next_node;
    }
    return result;
}

template <class T>
Node<T>* find_loop(const List<T>& list) {
    if (list.is_empty()) return nullptr;

    Node<T>* bunny = list.head(), *turtle = list.head();
    bool is_cycle = false;
    while (bunny != nullptr && turtle != nullptr) {
        if (bunny == turtle && is_cycle) break;
        bunny = bunny->_next;
        if (bunny == nullptr) break;
        if (!is_cycle)
            bunny = bunny->_next;
        turtle = turtle->_next;
        if (bunny == turtle && !is_cycle) {
            is_cycle = true;
            turtle = list.head();
        }
    }
    //list.tail()->_next = nullptr;
    if (is_cycle) return bunny;  // enter in destructor
    return nullptr;
}

#endif // !ALGORITHMS_ALGORITHMS_H