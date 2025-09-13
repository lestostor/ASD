#include "point3D.h"

Point3D::Point3D() : Point() {
    _z = 0;
}

Point3D::Point3D(int x, int y, int z) : Point(x, y), _z(z) {}

Point3D::Point3D(const Point& point) : Point(point), _z(0) {}

float Point3D::distance(const Point3D second) {
    int new_x = second._x - this->_x;
    int new_y = second._y - this->_y;
    int new_z = second._z - this->_z;
    return sqrt(new_x * new_x + new_y * new_y + new_z * new_z);
}

bool Point3D::operator==(const Point3D second) const {
    if (this->_x == second._x &&
        this->_y == second._y &&
        this->_z == second._z) return true;
    return false;
}