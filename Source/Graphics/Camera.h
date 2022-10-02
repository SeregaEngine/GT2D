#ifndef CAMERA_H_
#define CAMERA_H_

/* ====== INCLUDES ====== */
#include "GTMath.h"

/* ====== DEFINES ====== */
class Entity;

/* ====== STRUCTURES ====== */
class Camera
{
    s32 m_x, m_y; // If no entity attached this will be used
    SRect m_bounds;
    Entity* m_pAttached;
public:
    Camera() : m_x(0), m_y(0), m_bounds(0, 0, 0, 0), m_pAttached(nullptr) {}

    void SetPosition(s32 x, s32 y) { m_x = x; m_y = y; }
    void SetBounds(const SRect& bounds) { m_bounds = bounds; }
    void Attach(Entity* pEntity) { m_pAttached = pEntity; }
    void Detach();

    void GetPosition(s32& x, s32& y);
    const Entity* GetAttached() const { return m_pAttached; }
};

#endif // CAMERA_H_