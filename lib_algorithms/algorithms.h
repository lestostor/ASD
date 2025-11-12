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

bool check_math_expression(std::string);

template <class T>
bool is_looped_1(List<T> list) {
    if (list.begin() == list.end() && !list.is_empty()) {
        list.tail()->_next = nullptr;
        return true;
    }

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
            list.tail()->_next = nullptr;
            break;
        }
    }
    return result;
}

template <class T>
bool is_looped_2(List<T> list) {
    if (list.begin() == list.end() && !list.is_empty()) {
        list.tail()->_next = nullptr;
        return true;
    }
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
    list.tail()->_next = nullptr;
    return result;
}

template <class T>
Node<T>* find_loop(const List<T>& list) {
    Node<T>* result;
    if (list.tail() == nullptr) result =  nullptr;
    else result = list.tail()->_next;
    return result;
}

#endif // !ALGORITHMS_ALGORITHMS_H