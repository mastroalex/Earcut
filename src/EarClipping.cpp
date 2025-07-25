#ifdef USE_WOLFRAM_LIB

#include "WolframLibrary.h"
#include "EarClippingCore.h"
#include "Types.h"

EXTERN_C DLLEXPORT int TriangulateEarClipping(WolframLibraryData libData, mint Argc, MArgument* Args, MArgument Res) {
    if (Argc != 2) return LIBRARY_FUNCTION_ERROR;

    // ------- Arg 1: pts -------
    MTensor ptsTensor = MArgument_getMTensor(Args[0]);
    const mint* dims = libData->MTensor_getDimensions(ptsTensor);
    if (dims[1] != 2) return LIBRARY_FUNCTION_ERROR;

    mint nPts = dims[0];
    const double* ptsData = libData->MTensor_getRealData(ptsTensor);

    std::vector<Point> points(nPts);
    for (mint i = 0; i < nPts; ++i) {
        points[i] = { ptsData[2 * i], ptsData[2 * i + 1] };
    }

    // ------- Arg 2: conn -------
    MTensor connTensor = MArgument_getMTensor(Args[1]);
    mint nConn = libData->MTensor_getDimensions(connTensor)[0];
    const mint* connData = libData->MTensor_getIntegerData(connTensor);

    std::vector<int> conn(nConn);
    for (mint i = 0; i < nConn; ++i) {
        mint idx = connData[i];
        if (idx < 1 || idx > nPts) return LIBRARY_FUNCTION_ERROR; // Validate 1-based
        conn[i] = static_cast<int>(idx - 1); // convert to 0-based
    }

    // ------- Triangulation -------
    std::vector<Triangle> tris;
    if (!EarClipping::EarClippingTriangulate(points, conn, tris))
        return LIBRARY_FUNCTION_ERROR;

    // ------- Output: {nTriangles, 3} integer -------
    mint dimsOut[2] = { static_cast<mint>(tris.size()), 3 };
    MTensor out;
    libData->MTensor_new(MType_Integer, 2, dimsOut, &out);
    mint* outData = libData->MTensor_getIntegerData(out);

    for (mint i = 0; i < dimsOut[0]; ++i) {
        outData[i * 3 + 0] = tris[i].a + 1; // 1-based
        outData[i * 3 + 1] = tris[i].b + 1;
        outData[i * 3 + 2] = tris[i].c + 1;
    }

    *MArgument_getMTensorAddress(Res) = out;
    return LIBRARY_NO_ERROR;
}

#endif