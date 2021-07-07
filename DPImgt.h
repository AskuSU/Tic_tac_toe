#pragma once
#include <d2d1.h>

#pragma comment(lib, "d2d1")

class DPIScale
{
    static float scaleX;
    static float scaleY;

public:
    
    static void Initialize(ID2D1Factory* pFactory);

    template <typename T>
    static float PixelsToDipsX(T x);

    template <typename T>
    static float PixelsToDipsY(T y);
};