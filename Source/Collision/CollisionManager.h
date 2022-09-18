#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

/* ====== INCLUDES ====== */
#include "GTMath.h"

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class CollisionManager final : public EngineModule
{
public:
    CollisionManager() : EngineModule("CollisionManager", CHANNEL_GAME) {}

    b32f StartUp();
    void ShutDown();

    b32f IsOnGround(const Vector2& vPoint, const FRect& hitBox);
};

extern CollisionManager g_collisionMgr;

#endif // COLLISIONMANAGER_H_