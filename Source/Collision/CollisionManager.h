#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

/* ====== INCLUDES ====== */
#include "GTMath.h"
#include "TList.h"

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class Entity;

class CollisionManager final : public EngineModule
{
public:
    CollisionManager() : EngineModule("CollisionManager", CHANNEL_GAME) {}

    b32f StartUp();
    void ShutDown();

    b32f IsOnGround(const Vector2& vPoint, const FRect& hitBox) const;
    void GetCollidedEntities(const Vector2& vPoint, const FRect& hitBox,
                             TList<Entity*>& lstEntity, Entity* pExcept = nullptr) const;
};

extern CollisionManager g_collisionMgr;

#endif // COLLISIONMANAGER_H_