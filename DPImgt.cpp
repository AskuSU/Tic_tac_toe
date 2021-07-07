#include "DPImgt.h"

#pragma warning(disable : 4996)
inline void DPIScale::Initialize(ID2D1Factory* pFactory)
{
    FLOAT dpiX, dpiY;
    pFactory->GetDesktopDpi(&dpiX, &dpiY);
    scaleX = dpiX / 96.0f;
    scaleY = dpiY / 96.0f;
}

template<typename T>
inline float DPIScale::PixelsToDipsX(T x)
{
    return static_cast<float>(x) / scaleX;
}

template<typename T>
float DPIScale::PixelsToDipsY(T y)
{
    return static_cast<float>(y) / scaleY;
}

float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;