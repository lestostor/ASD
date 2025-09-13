#include "point.h"
#include <cmath>

Point::Point() {
    _x = 0;
    _y = 0;
}

Point::Point(int x, int y) : _x(x), _y(y) {}

float Point::distance(const Point second) {
    int new_x = second._x - this->_x;
    int new_y = second._y - this->_y;
    return sqrt(new_x * new_x + new_y * new_y);
}

bool Point::operator==(const Point second) const{
    if (this->_x == second._x &&
        this->_y == second._y) return true;
    return false;
}
