/* ====== INCLUDES ====== */
#include <math.h>

#include "GTMath.h"

/* ====== VARIABLES ====== */
f32 GTM::g_sinLook[361];
f32 GTM::g_cosLook[361];

/* ====== METHODS ====== */
b32 GTM::StartUp()
{
    // Sin/Cos look
    for (i32f i = 0; i < 361; ++i)
    {
        f32 angle = DEG_TO_RAD((f32)i);
        g_sinLook[i] = sinf(angle);
        g_cosLook[i] = cosf(angle);
    }

    return true;
}

void GTM::ShutDown()
{
}

s32 GTM::FastDist2(s32 x, s32 y)
{
    // Get absolute coordinates
    x = abs(x);
    y = abs(y);

    // Get minimal value
    s32 min = MIN(x, y);

    // Return distance
    return x + y - (min >> 1) - (min >> 2) + (min >> 4);
}

void GTM::TranslatePoly2(Poly2* poly, f32 dx, f32 dy)
{
    if (!poly)
        return;

    poly->x += dx;
    poly->y += dy;
}

void GTM::RotatePoly2(Poly2* poly, s32 angle)
{
    if (!poly)
        return;

    for (i32f i = 0; i < poly->vtxCount; ++i)
    {
        f32 x = poly->aVtx[i].x*g_cosLook[angle] - poly->aVtx[i].y*g_sinLook[angle];
        f32 y = poly->aVtx[i].x*g_sinLook[angle] + poly->aVtx[i].y*g_cosLook[angle];

        poly->aVtx[i].x = x;
        poly->aVtx[i].y = y;
    }
}

void GTM::ScalePoly2(Poly2* poly, f32 scaleX, f32 scaleY)
{
    if (!poly)
        return;

    for (i32f i = 0; i < poly->vtxCount; ++i)
    {
        poly->aVtx[i].x *= scaleX;
        poly->aVtx[i].y *= scaleY;
    }
}

b32 GTM::FindBoxPoly2(const Poly2* poly, f32& minX, f32& minY, f32& maxX, f32& maxY)
{
    // Check if polygon is correct
    if (!poly || poly->vtxCount <= 0)
        return false;

    // Init coords
    minX = minY = maxX = maxY = 0;

    // Find box
    for (i32f i = 0; i < poly->vtxCount; ++i)
    {
        if (poly->aVtx[i].x < minX)
            minX = poly->aVtx[i].x;
        if (poly->aVtx[i].x > maxX)
            maxX = poly->aVtx[i].x;

        if (poly->aVtx[i].y < minY)
            minY = poly->aVtx[i].y;
        if (poly->aVtx[i].y > maxY)
            maxY = poly->aVtx[i].y;
    }

    return true;
}
