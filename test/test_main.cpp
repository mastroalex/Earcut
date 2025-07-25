#ifndef USE_WOLFRAM_LIB

#include <iostream>
#include <vector>
#include "EarClippingCore.h"
#include "Geometry.h"
#include "Types.h"

int main() {
    // Define points
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

    std::vector<int> conn = {0, 1, 2, 3, 4, 5, 6, 7};

    std::vector<Triangle> tris;
    bool success = EarClipping::EarClippingTriangulate(pts, conn, tris);

    if (!success) {
        std::cerr << "Triangulation failed.\n";
        return 1;
    }

    // std::cout << "Triangles:\n";
    // for (const Triangle& tri : tris) {
    //     std::cout << "  ("
    //               << pts[tri.a].x << ", " << pts[tri.a].y << ") -> ("
    //               << pts[tri.b].x << ", " << pts[tri.b].y << ") -> ("
    //               << pts[tri.c].x << ", " << pts[tri.c].y << ")\n";
    // }
    std::cout << "Triangle connectivity:\n";
    for (const Triangle& tri : tris) {
        std::cout << "  " << tri.a << ", " << tri.b << ", " << tri.c << "\n";
    }
    return 0;
}

#endif // USE_WOLFRAM_LIB