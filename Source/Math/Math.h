#pragma once

#include <cstring>
#include <cmath>
#include "Engine/Types.h"
#include "Engine/Platform.h"

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

    forceinline Vector2() = default;
    forceinline Vector2(f32 _x, f32 _y) : x(_x), y(_y) {}
    forceinline Vector2(const Vector2& v) : x(v.x), y(v.y) {}
    forceinline ~Vector2() = default;

    forceinline Vector2 operator=(const Vector2& v)  { x = v.x; y = v.y; return *this; }
    forceinline Vector2 operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    forceinline Vector2 operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }

    forceinline Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
    forceinline Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
    forceinline Vector2 operator*(const Vector2& v) const { return { x * v.x, y * v.y }; }
    forceinline Vector2 operator*(f32 scalar) const { return { x * scalar, y * scalar }; }

    forceinline void Zero() { x = y = 0.0f; }
    forceinline void Init(f32 _x, f32 _y) { x = _x; y = _y; }
    forceinline f32 Length() const { return sqrtf(x*x + y*y); }

    forceinline Vector2 Normalize()
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

    forceinline FRect() = default;
    forceinline FRect(f32 _x1, f32 _y1, f32 _x2, f32 _y2) :
        x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

    forceinline FRect operator=(const FRect& rect)
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

    forceinline SRect() :
        x1(0), y1(0), x2(0), y2(0) {}
    forceinline SRect(s32 _x1, s32 _y1, s32 _x2, s32 _y2) :
        x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

    forceinline SRect operator=(const SRect& rect)
    {
        x1 = rect.x1;
        y1 = rect.y1;
        x2 = rect.x2;
        y2 = rect.y2;
        return *this;
    }
};

class Math
{
public:
    static constexpr f32 PI       = 3.141592654f;
    static constexpr f32 PI2      = 6.283185307f;
    static constexpr f32 PI_DIV_2 = 1.570796327f;
    static constexpr f32 PI_DIV_4 = 0.785398163f;
    static constexpr f32 PI_INV   = 0.318309886f;

    static constexpr f32 DEG_TO_RAD_MUL = PI / 180.0f;
    static constexpr f32 RAD_TO_DEG_MUL = 180.0f / PI;

public:
    f32 m_sinLook[361];
    f32 m_cosLook[361];

public:
    void StartUp();
    forceinline void ShutDown() {}

    forceinline static f32 DegToRad(f32 deg) noexcept
    {
        return deg * DEG_TO_RAD_MUL;
    }

    forceinline static f32 RadToDeg(f32 rad) noexcept
    {
        return rad * RAD_TO_DEG_MUL;
    }

    template<typename T>
    forceinline static T Max(T a, T b) noexcept
    {
        return a > b ? a : b;
    }

    template<typename T>
    forceinline static T Min(T a, T b) noexcept
    {
        return (a) < (b) ? (a) : (b);
    }

    template<typename T>
    forceinline static void Swap(T a, T b, T t) noexcept
    {
        t = a;
        a = b;
        b = t;
    }

    template<typename T>
    forceinline static T RandRange(T min, T max) noexcept
    {
        return min + (std::rand() % (max - min + 1));
    }

    /** @DEPRECATED */
    static s32 FastDist2(s32 x, s32 y);

    static void TranslatePoly2(Poly2* poly, f32 dx, f32 dy);
    static void RotatePoly2(Poly2* poly, s32 angle);
    static void ScalePoly2(Poly2* poly, f32 scaleX, f32 scaleY);
    static b32 FindBoxPoly2(const Poly2* poly, f32& minX, f32& minY, f32& maxX, f32& maxY);
};

inline Math g_math;