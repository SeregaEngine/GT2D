#pragma once

#include "Math/Math.h"

class Entity;

class Camera
{
    s32 m_x, m_y; // If no entity attached this will be used
    SRect m_bounds;
    Entity* m_pAttached;

public:
    Camera() : m_x(0), m_y(0), m_bounds(0, 0, 0, 0), m_pAttached(nullptr) {}

    forceinline void SetPosition(s32 x, s32 y) { m_x = x; m_y = y; }
    forceinline void SetBounds(const SRect& bounds) { m_bounds = bounds; }
    forceinline void Attach(Entity* pEntity) { m_pAttached = pEntity; }
    void Detach();

    void GetPosition(s32& x, s32& y);
    forceinline const Entity* GetAttached() const { return m_pAttached; }
};
