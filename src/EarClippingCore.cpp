#include "EarClippingCore.h"
#include "Geometry.h"
#include "Constants.h"
#include <algorithm>

namespace EarClipping {
    static bool isConvex(const Point& prev, const Point& curr, const Point& next) {
        Point a = curr - prev;
        Point b = next - curr;
        return a.cross(b) > 0;
    }


    bool EarClippingTriangulate(const std::vector<Point>& points, const std::vector<int>& polygon, std::vector<Triangle>& output) {
        size_t n = polygon.size();
        if (n < 3) return false;

        std::vector<int> indexList = polygon;

        int loopCount = 0;
        while (indexList.size() >= 3 && loopCount < 10000) {
            bool earFound = false;
            for (size_t i = 0; i < indexList.size(); ++i) {
                size_t prev = (i == 0) ? indexList.size() - 1 : i - 1;
                size_t next = (i + 1) % indexList.size();

                Point a = points[indexList[prev]];
                Point b = points[indexList[i]];
                Point c = points[indexList[next]];

                if (!isConvex(a, b, c)) continue;

                bool hasPointInside = false;
                for (size_t j = 0; j < indexList.size(); ++j) {
                    if (j == prev || j == i || j == next) continue;
                    Point p = points[indexList[j]];
                    if (PointInTriangle(p, a, b, c)) {
                        hasPointInside = true;
                        break;
                    }
                }
                if (hasPointInside) continue;

                for (size_t j = 0; j < indexList.size(); ++j) {
                    size_t jnext = (j + 1) % indexList.size();
                    if (j == prev || jnext == prev || j == i || jnext == i || j == next || jnext == next) continue;

                    Point p1 = points[indexList[j]];
                    Point p2 = points[indexList[jnext]];

                    if (SegmentsIntersect(a, c, p1, p2)) {
                        hasPointInside = true;
                        break;
                    }
                }
                if (hasPointInside) continue;

                output.emplace_back(indexList[prev], indexList[i], indexList[next]);
                indexList.erase(indexList.begin() + i);
                earFound = true;
                break;
            }
            if (!earFound) break;
            ++loopCount;
        }

        return (output.size() == n - 2);
    }
}