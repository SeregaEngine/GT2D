#pragma once

#include <cstring>
#include <cmath>
#include "Types.h"

#ifndef __forceinline
#define __forceinline inline
#endif

static constexpr f32 PI       = 3.141592654f;
static constexpr f32 PI2      = 6.283185307f;
static constexpr f32 PI_DIV_2 = 1.570796327f;
static constexpr f32 PI_DIV_4 = 0.785398163f;
static constexpr f32 PI_INV   = 0.318309886f;

static constexpr f32 DEG_TO_RAD_MUL = PI / 180.0f;
__forceinline static constexpr f32 DEG_TO_RAD(f32 deg) noexcept
{
    return deg * DEG_TO_RAD_MUL;
}

static constexpr f32 RAD_TO_DEG_MUL = 180.0f / PI;
__forceinline static constexpr f32 RAD_TO_DEG(f32 rad) noexcept
{
    return rad * RAD_TO_DEG_MUL;
}

template<typename T>
__forceinline static constexpr T MAX(T a, T b) noexcept
{
    return a > b ? a : b;
}

template<typename T>
__forceinline static constexpr T MIN(T a, T b) noexcept
{
    return (a) < (b) ? (a) : (b);
}

template<typename T>
__forceinline static constexpr void SWAP(T a, T b, T t) noexcept
{
    t = a;
    a = b;
    b = t;
}

template<typename T>
__forceinline static constexpr T RAND_RANGE(T min, T max) noexcept
{
    return min + (rand() % (max - min + 1));
}

struct Vector2
{
    union
    {
        f32 c[2];
        struct
        {
            f32 x, y;
        };
    };

    Vector2() = default;
    Vector2(f32 _x, f32 _y) : x(_x), y(_y) {}
    Vector2(const Vector2& v) : x(v.x), y(v.y) {}
    ~Vector2() = default;

    __forceinline Vector2 operator=(const Vector2& v)  { x = v.x; y = v.y; return *this; }
    __forceinline Vector2 operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    __forceinline Vector2 operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }

    __forceinline Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
    __forceinline Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
    __forceinline Vector2 operator*(const Vector2& v) const { return { x * v.x, y * v.y }; }
    __forceinline Vector2 operator*(f32 scalar) const { return { x * scalar, y * scalar }; }

    __forceinline void Zero() { x = 0.0f; y = 0.0f; }
    __forceinline void Init(f32 _x, f32 _y) { x = _x; y = _y; }
    __forceinline f32 Length() const { return sqrtf(x*x + y*y); }

    __forceinline Vector2 Normalize()
    {
        f32 invLength = 1.0f / Length();
        x *= invLength;
        y *= invLength;
        return *this;
    }
};

struct Poly2
{
    Vector2* aVtx;
    s32 vtxCount;
    f32 x, y;
    s32 state;
    s32 color;
};

struct FRect
{
    f32 x1, y1;
    f32 x2, y2;

    FRect() = default;
    FRect(f32 _x1, f32 _y1, f32 _x2, f32 _y2) :
        x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

    __forceinline FRect operator=(const FRect& rect)
    {
        x1 = rect.x1;
        y1 = rect.y1;
        x2 = rect.x2;
        y2 = rect.y2;
        return *this;
    }
};

struct SRect
{
    s32 x1, y1;
    s32 x2, y2;

    SRect() :
        x1(0), y1(0), x2(0), y2(0) {}
    SRect(s32 _x1, s32 _y1, s32 _x2, s32 _y2) :
        x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

    __forceinline SRect operator=(const SRect& rect)
    {
        x1 = rect.x1;
        y1 = rect.y1;
        x2 = rect.x2;
        y2 = rect.y2;
        return *this;
    }
};

namespace GTM
{
    /** Variables */
    inline f32 g_sinLook[361];
    inline f32 g_cosLook[361];

    /** Functions */
    extern b32 StartUp();
    static void ShutDown() {}

    /** @DEPRECATED */
    extern s32 FastDist2(s32 x, s32 y);

    extern void TranslatePoly2(Poly2* poly, f32 dx, f32 dy);
    extern void RotatePoly2(Poly2* poly, s32 angle);
    extern void ScalePoly2(Poly2* poly, f32 scaleX, f32 scaleY);
    extern b32 FindBoxPoly2(const Poly2* poly, f32& minX, f32& minY, f32& maxX, f32& maxY);
};
