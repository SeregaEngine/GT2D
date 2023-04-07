#include <cmath>
#include "Math/GTMath.h"

b32 Math::StartUp()
{
    // Sin/Cos look
    for (i32f i = 0; i < 361; ++i)
    {
        f32 angle = DegToRad((f32)i);
        m_sinLook[i] = sinf(angle);
        m_cosLook[i] = cosf(angle);
    }

    return true;
}

s32 Math::FastDist2(s32 x, s32 y)
{
    // Get absolute coordinates
    x = abs(x);
    y = abs(y);

    // Get minimal value
    s32 min = Min(x, y);

    // Return distance
    return x + y - (min >> 1) - (min >> 2) + (min >> 4);
}

void Math::TranslatePoly2(Poly2* poly, f32 dx, f32 dy)
{
    if (!poly)
    {
        return;
    }

    poly->x += dx;
    poly->y += dy;
}

void Math::RotatePoly2(Poly2* poly, s32 angle)
{
    if (!poly)
    {
        return;
    }

    for (i32f i = 0; i < poly->vtxCount; ++i)
    {
        f32 x = poly->aVtx[i].x*g_math.m_cosLook[angle] - poly->aVtx[i].y*g_math.m_sinLook[angle];
        f32 y = poly->aVtx[i].x*g_math.m_sinLook[angle] + poly->aVtx[i].y*g_math.m_cosLook[angle];

        poly->aVtx[i].x = x;
        poly->aVtx[i].y = y;
    }
}

void Math::ScalePoly2(Poly2* poly, f32 scaleX, f32 scaleY)
{
    if (!poly)
    {
        return;
    }

    for (i32f i = 0; i < poly->vtxCount; ++i)
    {
        poly->aVtx[i].x *= scaleX;
        poly->aVtx[i].y *= scaleY;
    }
}

b32 Math::FindBoxPoly2(const Poly2* poly, f32& minX, f32& minY, f32& maxX, f32& maxY)
{
    // Check if polygon is correct
    if (!poly || poly->vtxCount <= 0)
    {
        return false;
    }

    // Init coords
    minX = minY = maxX = maxY = 0;

    // Find box
    for (i32f i = 0; i < poly->vtxCount; ++i)
    {
        if (poly->aVtx[i].x < minX) minX = poly->aVtx[i].x;
        if (poly->aVtx[i].x > maxX) maxX = poly->aVtx[i].x;

        if (poly->aVtx[i].y < minY) minY = poly->aVtx[i].y;
        if (poly->aVtx[i].y > maxY) maxY = poly->aVtx[i].y;
    }

    return true;
}
