#ifndef UNIT_H_
#define UNIT_H_

#include "Types.h"

namespace GTU
{
    /* ====== INTERNAL VARIABLES ====== */
    extern f32 s_unitX; // Pixels per unit
    extern f32 s_unitY;

    /* ====== FUNCTIONS ====== */
    __forceinline void UnitToScreen(f32& x, f32& y) { x *= s_unitX; y *= s_unitY; }
    __forceinline f32 UnitToScreenX(f32 x) { return x * s_unitX; }
    __forceinline f32 UnitToScreenY(f32 y) { return y * s_unitY; }

    __forceinline void ScreenToUnit(f32& x, f32& y) { x /= s_unitX; y /= s_unitY; }
    __forceinline f32 ScreenToUnitX(f32 x) { return x / s_unitX; }
    __forceinline f32 ScreenToUnitY(f32 y) { return y / s_unitY; }

    __forceinline f32 GetUnitX() { return s_unitX; }
    __forceinline f32 GetUnitY() { return s_unitY; }

    /* === Only for Graphics Module! === */
    inline void SetUnitXY(f32 x, f32 y) { s_unitX = x; s_unitY = y; }
}

#endif // UNIT_H_