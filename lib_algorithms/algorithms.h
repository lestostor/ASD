#ifndef ALGORITHMS_ALGORITHMS_H
#define ALGORITHMS_ALGORITHMS_H

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

enum Type { intersect, touch, inside, not_touch };

Type check_circles(Circle, Circle);

Type check_spheres(Sphere, Sphere);

#endif // !ALGORITHMS_ALGORITHMS_H