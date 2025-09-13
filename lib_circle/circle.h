#ifndef CIRCLE_CIRCLE_H
#define CIRCLE_CIRCLE_H

#include "../lib_point/point.h"

class Circle {
    Point _centre;
    float _radius;
public:
    Circle();
    Circle(Point, int);
    Circle(int, int, float);
    Circle(const Circle&);

    float get_radius();
    Point get_centre();
};

#endif // !CIRCLE_CIRCLE_H