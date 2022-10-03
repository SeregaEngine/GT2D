/* TODO
 * - Sin/CosLook(f32 angle) fast version
 */

#ifndef GTMATH_H_
#define GTMATH_H_

/* ====== INCLUDES ====== */
#include <string.h> // memcpy/memset()
#include <math.h>

#include "Types.h"

/* ====== DEFINES ====== */
#ifndef __forceinline
#define __forceinline inline
#endif

#define PI       3.141592654f
#define PI2      6.283185307f
#define PI_DIV_2 1.570796327f
#define PI_DIV_4 0.785398163f
#define PI_INV   0.318309886f

#define DEG_TO_RAD(DEG) ((DEG) * PI/180)
#define RAD_TO_DEG(RAD) ((RAD) * 180/PI)

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define SWAP(A, B, T) { T = A; A = B; B = T; }
#define RAND_RANGE(MIN, MAX) ( (MIN) + ( rand() % ((MAX) - (MIN) + 1)) )

/* ====== STRUCTURES ====== */

/* === Vector === */
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

    __forceinline Vector2 operator=(const Vector2& v) { x = v.x; y = v.y; return *this; }
    __forceinline Vector2 operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
    __forceinline Vector2 operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }

    __forceinline Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
    __forceinline Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
    __forceinline Vector2 operator*(const Vector2& v) const { return { x * v.x, y * v.y }; }
    __forceinline Vector2 operator*(f32 scalar) const { return { x * scalar, y * scalar }; }

    __forceinline void Zero() { x = 0.0f; y = 0.0f; }
    __forceinline void Init(f32 _x, f32 _y) { x = _x; y = _y; }
    __forceinline f32 Length() const { return sqrtf(x*x + y*y); }
    __forceinline Vector2 Normalize() { f32 len = Length(); x /= len; y /= len; return *this; }
};

/* === Polygon === */
struct Poly2
{
    Vector2* aVtx;
    s32 vtxCount;
    f32 x, y;
    s32 state;
    s32 color;
};

/* === Rectangle === */
struct FRect
{
    f32 x1, y1;
    f32 x2, y2;

    FRect() = default;
    FRect(f32 _x1, f32 _y1, f32 _x2, f32 _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

    FRect operator=(const FRect& rect) {
        x1 = rect.x1; y1 = rect.y1; x2 = rect.x2; y2 = rect.y2; return *this;
    }
};

struct SRect
{
    s32 x1, y1;
    s32 x2, y2;

    SRect()
        : x1(0), y1(0), x2(0), y2(0) {}
    SRect(s32 _x1, s32 _y1, s32 _x2, s32 _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    SRect operator=(const SRect& rect) {
        x1 = rect.x1; y1 = rect.y1; x2 = rect.x2; y2 = rect.y2; return *this;
    }
};

/* ====== LIBRARY NAMESPACE ====== */
namespace GTM
{
    /* === Variables === */
    extern f32 g_sinLook[361];
    extern f32 g_cosLook[361];

    /* === Functions === */
    extern b32 StartUp();
    extern void ShutDown();

    // Fast distance functions returns distance between zero point and xy/xyz point
    extern s32 FastDist2(s32 x, s32 y);

    /* Polygon */
    extern void TranslatePoly2(Poly2* poly, f32 dx, f32 dy);
    extern void RotatePoly2(Poly2* poly, s32 angle);
    extern void ScalePoly2(Poly2* poly, f32 scaleX, f32 scaleY);
    extern b32 FindBoxPoly2(const Poly2* poly, f32& minX, f32& minY, f32& maxX, f32& maxY);
};

#endif // GTMATH_H_
