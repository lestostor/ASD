#ifndef POINT3D_POINT3D_H
#define POINT3D_POINT3D_H

#include "../lib_point/point.h"
#include <cmath>

class Point3D : public Point {
    int _z;
public:
    Point3D();
    Point3D(int, int, int);
    Point3D(const Point&);
    Point3D(const Point3D&) = default;

    float distance(const Point3D);

    bool operator==(const Point3D) const;
};
#endif // !POINT3D_POINT3D_H
