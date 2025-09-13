#ifndef SPHERE_SPHERE_H
#define SPHERE_SPHERE_H

#include "../lib_point3D/point3D.h"

class Sphere {
    Point3D _centre;
    float _radius;

public:
    Sphere();
    Sphere(Point3D, int);
    Sphere(int, int, int, float);
    Sphere(const Sphere&);

    float get_radius();
    Point3D get_centre();
};

#endif // !SPHERE_SPHERE_H