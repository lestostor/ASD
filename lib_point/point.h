#ifndef POINT_POINT_H
#define POINT_POINT_H


class Point {
protected:
    int _x;
    int _y;
public:
    Point();
    Point(int, int);
    Point(const Point&) = default;

    float distance(const Point);

    bool operator==(const Point) const;
};

#endif // !POINT_POINT_H