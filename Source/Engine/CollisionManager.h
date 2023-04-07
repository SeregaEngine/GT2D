#pragma once

#include "Math/GTMath.h"
#include "Containers/List.h"
#include "Engine/EngineModule.h"

class Entity;

class CollisionManager final : public EngineModule
{
public:
    CollisionManager() : EngineModule("CollisionManager", CHANNEL_GAME) {}

    b32 StartUp();
    void ShutDown();

    b32 IsOnGround(const Vector2& vPoint, const FRect& hitBox) const;
    void CheckCollision(const Vector2& vPoint, const FRect& hitBox, TList<Entity*>& lstEntity, const Entity* pExcept = nullptr) const;
    void CheckCollision(const Vector2& vPoint, const FRect& hitBox, b32 (*predicate)(Entity*, void*), void* userdata, TList<Entity*>& lstEntity, const Entity* pExcept = nullptr) const;
};

inline CollisionManager g_collisionMgr;
