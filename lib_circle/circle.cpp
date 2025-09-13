#include "circle.h"
#include <iostream>

Circle::Circle() {
    _radius = 1;
}

Circle::Circle(Point centre, int rad) : _centre(centre) {
    if (rad <= 0)
        throw std::invalid_argument("Radius can't be <= 0");
    _radius = rad;
}

Circle::Circle(int x, int y, float rad) : _centre(x, y) {
    if (rad <= 0)
        throw std::invalid_argument("Radius can't be <= 0");
    _radius = rad;
}

Circle::Circle(const Circle& other) {
    this->_centre = other._centre;
    this->_radius = other._radius;
}

float Circle::get_radius() { return _radius; }

Point Circle::get_centre() { return _centre; }