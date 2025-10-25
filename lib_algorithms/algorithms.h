#ifndef ALGORITHMS_ALGORITHMS_H
#define ALGORITHMS_ALGORITHMS_H

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"
#include "../lib_stack/stack.h"
#include <string>

enum Type { intersect, touch, inside, not_touch };

Type check_circles(Circle, Circle);

Type check_spheres(Sphere, Sphere);

bool check_brackets(std::string);

bool check_math_expression(std::string);

#endif // !ALGORITHMS_ALGORITHMS_H