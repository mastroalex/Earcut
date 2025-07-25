# Earcut++
A C++ library to triangulate polygons, that actually works.

This C++ library implements the **Ear Clipping algorithm** for polygon triangulation. It's designed to be lightweight and more performant than alternatives `poly2tri`, able to easly deal with concave polygons.

![Demo](imgs/README-1753372224153.png)

## 🚀 Features

- Fast triangulation of simple polygons
- Header-only interface for easy integration
- No third-party dependencies

## 📦 Structure

- `include/` — Public headers
- `src/` — Implementation files
- `test/` — (Optional) Tests and benchmarks

## 🛠️ Build

```bash
make
```

Or use your own build system, just include the headers and link the sources.

## ⚙️ Integration with Wolfram Mathematica


📄 Example Usage

```cpp
#include "EarClippingCore.h"
#include "Geometry.h"

int main() {
    Polygon poly = {/* your points here */};
    std::vector<Triangle> result = EarClipping::triangulate(poly);
    return 0;
}
```

## Computational cost



