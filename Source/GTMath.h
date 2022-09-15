#ifndef GTMATH_H_
#define GTMATH_H_

/* ====== INCLUDES ====== */
#include <string.h> // memcpy/memset()

#include "Types.h"

/* ====== DEFINES ====== */
#ifndef __forceinline
#define __forceinline inline
#endif

#define PI       3.1415926535f
#define PI2      6.283185307f
#define PI_DIV_2 1.570796327f
#define PI_DIV_4 0.785398163f
#define PI_INV   0.318309886f

#define EPSILON_E4 (f32)(1e-4)
#define EPSILON_E5 (f32)(1e-5)
#define EPSILON_E6 (f32)(1e-6)

#define PARAM_LINE_NO_INTERSECT            0
#define PARAM_LINE_INTERSECT_IN            1
#define PARAM_LINE_NO_INTERSECT_OUT        2
#define PARAM_LINE_NO_INTERSECT_EVERYWHERE 3


#define DEG_TO_RAD(DEG) ((DEG) * PI/180)
#define RAD_TO_DEG(RAD) ((RAD) * 180/PI)

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define SWAP(A, B, T) { T = A; A = B; B = T; }
#define RAND_RANGE(MIN, MAX) ( (MIN) + ( rand() % ((MAX) - (MIN) + 1)) )

/* ====== STRUCTURES ====== */

/* === Vector === */
typedef struct Vec2_t
{
    union
    {
        f32 c[2];
        struct
        {
            f32 x, y;
        };
    };

    Vec2_t() = default;
    Vec2_t(f32 _x, f32 _y) : x(_x), y(_y) {}
    Vec2_t(const Vec2_t& v) : x(v.x), y(v.y) {}
    Vec2_t operator=(const Vec2_t& v) { x = v.x; y = v.y; return *this; }
    ~Vec2_t() = default;
} Vec2, Point2, Vtx2;

typedef struct Vec3_t
{
    union
    {
        f32 c[3];
        struct
        {
            f32 x, y, z;
        };
    };
} Vec3, Point3, Vtx3;

typedef struct Vec4_t
{
    union
    {
        f32 c[4];
        struct
        {
            f32 x, y, z, w;
        };
    };
} Vec4, Point4, Vtx4;

/* === Parametric Line === */
struct ParamLine2
{
    Point2 p0, p1; // Start, end
    Vec2 v;        // Direction vector of line segment
};

struct ParamLine3
{
    Point3 p0, p1; // Start, end
    Vec3 v;        // Direction vector of line segment
};

/* === Plane === */
struct Plane3
{
    Point3 p0; // Point
    Vec3 n;    // Normal to the plane
};

/* === Matrice === */
struct Mat44
{
    union
    {
        f32 c[4][4];
        struct
        {
            f32 c00, c01, c02, c03;
            f32 c10, c11, c12, c13;
            f32 c20, c21, c22, c23;
            f32 c30, c31, c32, c33;
        };
    };
};

struct Mat43
{
    union
    {
        f32 c[4][3];
        struct
        {
            f32 c00, c01, c02;
            f32 c10, c11, c12;
            f32 c20, c21, c22;
            f32 c30, c31, c32;
        };
    };
};

struct Mat14
{
    union
    {
        f32 c[4];
        struct
        {
            f32 c00, c01, c02, c03;
        };
    };
};

struct Mat33
{
    union
    {
        f32 c[3][3];
        struct
        {
            f32 c00, c01, c02;
            f32 c10, c11, c12;
            f32 c20, c21, c22;
        };
    };
};

struct Mat32
{
    union
    {
        f32 c[3][2];
        struct
        {
            f32 c00, c01;
            f32 c10, c11;
            f32 c20, c21;
        };
    };
};

struct Mat13
{
    union
    {
        f32 c[3];
        struct
        {
            f32 c00, c01, c02;
        };
    };
};

struct Mat22
{
    union
    {
        f32 c[2][2];
        struct
        {
            f32 c00, c01;
            f32 c10, c11;
        };
    };
};

struct Mat12
{
    union
    {
        f32 c[2];
        struct
        {
            f32 c00, c01;
        };
    };
};

/* === Quaternion === */
struct Quat
{
    union
    {
        f32 c[4]; // Array of components
        
        struct // q0 + qv
        {
            f32 q0;  // Real part
            Vec3 qv; // Imaginary part
        };

        struct // Vector-like
        {
            f32 w, x, y, z;
        };
    };
};

/* === Polar === */
struct Polar2
{
    f32 r, theta;
};

/* === Cylindrical === */
struct Cylin3
{
    f32 r, theta, z;
};

/* === Spherical === */
struct Spher3
{
    f32 p; // Distance to the point from the origin
    f32 theta; // The angle from z-axis
    f32 phi; // The angle from the projection if o->p onto the x-y plane and x-axis
};

/* === Polygon === */
struct Poly2
{
    s32 state;
    s32 vtxCount;
    f32 x, y;
    f32 vx, vy;
    s32 color;
    Vtx2* aVtx;
};

/* === Rectangle === */
struct FRect
{
    f32 x1, y1;
    f32 x2, y2;

    FRect()
        : x1(0.0f), y1(0.0f), x2(0.0f), y2(0.0f) {}
    FRect(f32 _x1, f32 _y1, f32 _x2, f32 _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    FRect operator=(const FRect& rect)
    {
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
    extern f32 sinLook[361];
    extern f32 cosLook[361];

    extern const Mat44 g_IMat44;
    extern const Mat43 g_IMat43;
    extern const Mat33 g_IMat33;
    extern const Mat22 g_IMat22;

    /* === Functions === */
    extern b32 StartUp();
    extern void ShutDown();

    // Fast distance functions return distance between zero point and xy/xyz point
    extern s32 FastDist2(s32 x, s32 y);
    extern f32 FastDist3(f32 x, f32 y, f32 z);

    /* Vector */
    __forceinline void ZeroVec2(Vec2* v) { v->x = 0.0f; v->y = 0.0f; }
    __forceinline void ZeroVec3(Vec3* v) { v->x = 0.0f; v->y = 0.0f; v->z = 0; }
    __forceinline void ZeroVec4(Vec4* v) { v->x = 0.0f; v->y = 0.0f; v->z = 0; v->w = 1; }

    __forceinline void InitVec2(Vec2* v, f32 x, f32 y) { v->x = x; v->y = y; }
    __forceinline void InitVec3(Vec3* v, f32 x, f32 y, f32 z) { v->x = x; v->y = y; v->z = z; }
    __forceinline void InitVec4(Vec4* v, f32 x, f32 y, f32 z) { v->x = x; v->y = y; v->z = z; v->w = 1; }

    __forceinline void CopyVec2(Vec2* dst, const Vec2* src) { dst->x = src->x; dst->y = src->y; }
    __forceinline void CopyVec3(Vec3* dst, const Vec3* src) { dst->x = src->x; dst->y = src->y; dst->z = src->z; }
    __forceinline void CopyVec4(Vec4* dst, const Vec4* src) { dst->x = src->x; dst->y = src->y; dst->z = src->z; dst->w = src->w; }

    __forceinline Vec2 AddVec2(const Vec2* v1, const Vec2* v2) { return { v1->x + v2->x, v1->y + v2->y }; }
    __forceinline void AddVec2(const Vec2* v1, const Vec2* v2, Vec2* vr) { vr->x = v1->x + v2->x; vr->y = v1->y + v2->y; }

    /* Matrice */
    __forceinline void ZeroMat22(Mat22* m) { memset(m, 0, sizeof(*m)); }
    __forceinline void ZeroMat33(Mat33* m) { memset(m, 0, sizeof(*m)); }
    __forceinline void ZeroMat44(Mat44* m) { memset(m, 0, sizeof(*m)); }
    __forceinline void ZeroMat43(Mat43* m) { memset(m, 0, sizeof(*m)); }

    __forceinline void IdentityMat22(Mat22* m) { memcpy(m, &g_IMat22, sizeof(*m)); }
    __forceinline void IdentityMat33(Mat33* m) { memcpy(m, &g_IMat33, sizeof(*m)); }
    __forceinline void IdentityMat44(Mat44* m) { memcpy(m, &g_IMat44, sizeof(*m)); }
    __forceinline void IdentityMat43(Mat43* m) { memcpy(m, &g_IMat43, sizeof(*m)); }

    __forceinline void CopyMat22(Mat22* dst, const Mat22* src) { memcpy(dst, src, sizeof(*dst)); }
    __forceinline void CopyMat33(Mat33* dst, const Mat33* src) { memcpy(dst, src, sizeof(*dst)); }
    __forceinline void CopyMat44(Mat44* dst, const Mat44* src) { memcpy(dst, src, sizeof(*dst)); }
    __forceinline void CopyMat43(Mat43* dst, const Mat43* src) { memcpy(dst, src, sizeof(*dst)); }

    __forceinline void TransposeMat33(Mat33* m) {
        Mat33 mt = { m->c00, m->c10, m->c20,
                     m->c01, m->c11, m->c21,
                     m->c02, m->c12, m->c22 };
        memcpy(m, &mt, sizeof(*m));
    }

    __forceinline void TransposeMat44(Mat44* m) {
        Mat44 mt = { m->c00, m->c10, m->c20, m->c30,
                     m->c01, m->c11, m->c21, m->c31,
                     m->c02, m->c12, m->c22, m->c32,
                     m->c03, m->c13, m->c23, m->c33 };
        memcpy(m, &mt, sizeof(*m));
    }

    __forceinline void TransposeMat33(Mat33* dst, Mat33* src) {
        dst->c00 = src->c00; dst->c01 = src->c10; dst->c02 = src->c20;
        dst->c10 = src->c01; dst->c11 = src->c11; dst->c12 = src->c21;
        dst->c20 = src->c02; dst->c21 = src->c12; dst->c22 = src->c22;
    }

    __forceinline void TransposeMat44(Mat44* dst, Mat44* src) {
        dst->c00 = src->c00; dst->c01 = src->c10; dst->c02 = src->c20; dst->c03 = src->c30;
        dst->c10 = src->c01; dst->c11 = src->c11; dst->c12 = src->c21; dst->c13 = src->c31;
        dst->c20 = src->c02; dst->c21 = src->c12; dst->c22 = src->c22; dst->c23 = src->c32;
        dst->c30 = src->c03; dst->c31 = src->c13; dst->c32 = src->c23; dst->c33 = src->c33;
    }

    __forceinline void SwapColumnMat22(Mat22* m, s32 c, const Mat12* v)
        { m->c[0][c] = v->c[0]; m->c[1][c] = v->c[1]; }

    __forceinline void SwapColumnMat33(Mat33* m, s32 c, const Mat13* v)
        { m->c[0][c] = v->c[0]; m->c[1][c] = v->c[1]; m->c[2][c] = v->c[2]; }

    __forceinline void SwapColumnMat44(Mat44* m, s32 c, const Mat14* v)
        { m->c[0][c] = v->c[0]; m->c[1][c] = v->c[1]; m->c[2][c] = v->c[2]; m->c[3][c] = v->c[3]; }

    __forceinline void SwapColumnMat43(Mat43* m, s32 c, const Mat14* v)
        { m->c[0][c] = v->c[0]; m->c[1][c] = v->c[1]; m->c[2][c] = v->c[2]; m->c[3][c] = v->c[3]; }

    extern void MulMat33(const Mat33* m1, const Mat33* m2, Mat33* mr);
    extern void MulMat13x33(const Mat13* m1, const Mat33* m2, Mat13* mr);
    extern void MulMat12x32(const Mat12* m1, const Mat32* m2, Mat12* mr);

    /* Quaternion */
    __forceinline void ZeroQuat(Quat* q) { q->w = q->x = q->y = q->z = 0.0f; }
    __forceinline void InitQuat(Quat* q, f32 w, f32 x, f32 y, f32 z) { q->w = w; q->x = x; q->y = y; q->z = z; }
    __forceinline void InitQuat(Quat* q, Vec3* v) { q->w = 0.0f; q->x = v->x; q->y = v->y; q->z = v->z; }
    __forceinline void InitQuat(Quat* dst, const Quat* src) { dst->w = src->w; dst->x = src->x; dst->y = src->y; dst->z = src->z; }
    __forceinline void CopyQuat(Quat* dst, const Quat* src) { dst->w = src->w; dst->x = src->x; dst->y = src->y; dst->z = src->z; }

    /* Polygon */
    extern void TranslatePoly2(Poly2* poly, f32 dx, f32 dy);
    extern void RotatePoly2(Poly2* poly, s32 angle);
    extern void ScalePoly2(Poly2* poly, f32 scaleX, f32 scaleY);
    extern b32 FindBoxPoly2(const Poly2* poly, f32 minX, f32 minY, f32 maxX, f32 maxY);
};

#endif // GTMATH_H_
