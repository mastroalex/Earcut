#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "EarClippingCore.h"
#include "Types.h"

using namespace std;
using namespace std::chrono;

std::vector<Point> generateRandomPolygon(int n, double radius = 1.0) {
    std::vector<Point> pts(n);
    double angleStep = 2 * M_PI / n;
    for (int i = 0; i < n; ++i) {
        double angle = i * angleStep;
        pts[i] = {radius * cos(angle), radius * sin(angle)};
    }
    return pts;
}

std::vector<int> makeConn(int n) {
    std::vector<int> conn(n);
    for (int i = 0; i < n; ++i) conn[i] = i;
    return conn;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertsPerPoly(10, 100);

    cout << "NumPolygons,TotalTime_ms\n";

    for (int nPolys = 10; nPolys <= 1000000; nPolys *= 10) {
        vector<vector<Point>> allPolys;
        vector<vector<int>> allConns;

        for (int i = 0; i < nPolys; ++i) {
            int nVerts = vertsPerPoly(gen);
            allPolys.push_back(generateRandomPolygon(nVerts));
            allConns.push_back(makeConn(nVerts));
        }

        vector<Triangle> tris;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < nPolys; ++i) {
            vector<Triangle> tmp;
            bool ok = EarClipping::EarClippingTriangulate(allPolys[i], allConns[i], tmp);
            if (!ok) {
                cerr << "Triangulation failed on polygon " << i << endl;
            }
            tris.insert(tris.end(), tmp.begin(), tmp.end());
        }
        auto end = high_resolution_clock::now();
        auto ms = duration_cast<milliseconds>(end - start).count();

        cout << nPolys << "," << ms << "\n";
    }

    return 0;
}