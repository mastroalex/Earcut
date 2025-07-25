#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Types.h"
#include "Constants.h"

bool PointInTriangle(const Point& p, const Point& a, const Point& b, const Point& c);
bool PointOnLine(const Point& p, const Point& a, const Point& b);
bool SegmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2);

#endif // GEOMETRY_H
