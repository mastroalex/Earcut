#ifndef EAR_CLIPPING_CORE_H
#define EAR_CLIPPING_CORE_H

#include <vector>
#include "Types.h"

namespace EarClipping {


bool EarClippingTriangulate(const std::vector<Point>& points,
                            const std::vector<int>& polygon,
                            std::vector<Triangle>& output);

}

#endif // EAR_CLIPPING_CORE_H