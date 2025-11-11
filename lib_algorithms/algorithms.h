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
bool is_looped_1(List<T>& list) {
    if (list.begin() == list.end() && !list.is_empty()) return true;

    List<T>::Iterator bunny = list.begin(),
        turtle = list.begin();
    while (bunny != nullptr && turtle != nullptr) {
        bunny++;
        if (bunny == nullptr)
            return false;
        bunny++;
        turtle++;
        if (bunny == turtle)
            return true;
    }
    return false;
}

template <class T>
bool is_looped_2(List<T>& list);

#endif // !ALGORITHMS_ALGORITHMS_H