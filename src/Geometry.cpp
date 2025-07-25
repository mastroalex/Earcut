#include "Geometry.h"
#include <cmath>

bool PointInTriangle(const Point& pt, const Point& a, const Point& b, const Point& c) {
    Point v0 = c - a;
    Point v1 = b - a;
    Point v2 = pt - a;

    double dot00 = v0.dot(v0);
    double dot01 = v0.dot(v1);
    double dot02 = v0.dot(v2);
    double dot11 = v1.dot(v1);
    double dot12 = v1.dot(v2);

    double denom = dot00 * dot11 - dot01 * dot01;
    if (std::abs(denom) < EPSILON) return false;

    double invDenom = 1.0 / denom;
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

bool PointOnLine(const Point& p, const Point& a, const Point& b) {
    Point ab = b - a;
    Point ap = p - a;
    return std::abs(ab.cross(ap)) < EPSILON;
}

bool SegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2) {
    Point r = p2 - p1;
    Point s = q2 - q1;
    Point pq = q1 - p1;

    double rxs = r.cross(s);
    if (std::abs(rxs) < EPSILON) return false;

    double t = pq.cross(s) / rxs;
    double u = pq.cross(r) / rxs;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}


