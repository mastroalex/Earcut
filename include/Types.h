#ifndef TYPES_H
#define TYPES_H

#include <vector>

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    double dot(const Point& p) const {
        return x * p.x + y * p.y;
    }

    double cross(const Point& p) const {
        return x * p.y - y * p.x;
    }
};

using Polygon = std::vector<Point>;

struct Triangle {
    int a, b, c;
    Triangle(int a, int b, int c) : a(a), b(b), c(c) {}
};

#endif // TYPES_H
