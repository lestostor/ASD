#include "sphere.h"
#include <iostream>

Sphere::Sphere() {
    _radius = 1;
}

Sphere::Sphere(Point3D centre, int rad) : _centre(centre) {
    if (rad <= 0)
        throw std::invalid_argument("Radius can't be <= 0");
    _radius = rad;
}

Sphere::Sphere(int x, int y, int z, float rad) : _centre(x, y, z) {
    if (rad <= 0)
        throw std::invalid_argument("Radius can't be <= 0");
    _radius = rad;
}

Sphere::Sphere(const Sphere& other) {
    this->_centre = other._centre;
    this->_radius = other._radius;
}

float Sphere::get_radius() { return _radius; }

Point3D Sphere::get_centre() { return _centre; }