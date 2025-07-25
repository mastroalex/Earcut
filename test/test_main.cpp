#include <iostream>
#include <vector>
#include "EarClippingCore.h"
#include "Geometry.h"
#include "Types.h"

int main() {
    // Define points (0.015 offset applied)
    std::vector<Point> pts = {
        {0.915, 0.0},
        {0.915, 0.15},
        {0.265, 0.15},
        {0.265, 0.65},
        {0.915, 0.65},
        {0.915, 0.8},
        {0.115, 0.8},
        {0.115, 0.0}
    };

    // Define connectivity (1-based to 0-based indexing)
    std::vector<size_t> conn = {0, 1, 2, 3, 4, 5, 6, 7};

    // Construct polygon
    Polygon poly;
    for (size_t idx : conn) {
        poly.push_back(pts[idx]);
    }

    // Triangulate
    std::vector<Triangle> triangles = EarClipping::triangulate(poly);

    // Output triangles
    std::cout << "Triangles:\n";
    for (const auto& tri : triangles) {
        std::cout << "  ("
                  << tri.a.x << ", " << tri.a.y << ") -> ("
                  << tri.b.x << ", " << tri.b.y << ") -> ("
                  << tri.c.x << ", " << tri.c.y << ")\n";
    }

    return 0;
}