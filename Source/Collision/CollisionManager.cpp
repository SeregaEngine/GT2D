/* ====== INCLUDES ====== */
#include "Game.h"

#include "CollisionManager.h"

/* ====== GLOBALS ====== */
CollisionManager g_collisionMgr;

/* ====== METHODS ====== */
b32f CollisionManager::StartUp()
{
    AddNote(PR_NOTE, "Module started");

    return true;
}

void CollisionManager::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

b32f CollisionManager::IsOnGround(const Vector2& vPoint, const FRect& hitBox) const
{
    const SRect& ground = g_game.GetWorld().GetGroundBounds();

    if (vPoint.y + hitBox.y2 >= ground.y1 && vPoint.y + hitBox.y2 <= ground.y2 &&
        vPoint.x + hitBox.x1 >= ground.x1 && vPoint.x + hitBox.x2 <= ground.x2)
        return true;
    return false;
}

void CollisionManager::CheckCollision(const Vector2& vPoint, const FRect& hitBox, TList<Entity*>& lstEntity, Entity* pExcept) const
{
    // Get hitbox in world coords
    FRect rect = {
        vPoint.x + hitBox.x1, vPoint.y + hitBox.y1,
        vPoint.x + hitBox.x2, vPoint.y + hitBox.y2
    };

    // Try to find entities that lie on the rectangle
    auto& lstWorldEntity = g_game.GetWorld().GetEntityList();
    auto end = lstWorldEntity.End();

    for (auto it = lstWorldEntity.Begin(); it != end; ++it)
    {
        if (it->data == pExcept || !it->data->IsCollidable())
            continue;

        const Vector2& vPosition = it->data->GetPosition();
        if (vPosition.x >= rect.x1 && vPosition.x <= rect.x2 &&
            vPosition.y >= rect.y1 && vPosition.y <= rect.y2)
        {
            lstEntity.Push(it->data);
        }
    }
}

void CollisionManager::CheckCollision(const Vector2& vPoint, const FRect& hitBox, b32f (*predicate)(Entity*, void*), void* userdata, TList<Entity*>& lstEntity, Entity* pExcept) const
{
    // Get check hitbox in world coords
    FRect checkRect = {
        vPoint.x + hitBox.x1, vPoint.y + hitBox.y1,
        vPoint.x + hitBox.x2, vPoint.y + hitBox.y2
    };

    // Try to find entities that lie on the rectangle
    auto& lstWorldEntity = g_game.GetWorld().GetEntityList();
    auto end = lstWorldEntity.End();

    for (auto it = lstWorldEntity.Begin(); it != end; ++it)
    {
        if (it->data == pExcept || !it->data->IsCollidable() || !predicate(it->data, userdata))
            continue;

        // Get entity hitbox in world coords
        const Vector2& vEntity = it->data->GetPosition();
        const FRect& entityBox = it->data->GetHitBox();
        FRect entityRect = {
            vEntity.x + entityBox.x1, vEntity.y + entityBox.y1,
            vEntity.x + entityBox.x2, vEntity.y + entityBox.y2
        };

        // Check collision
        if (entityRect.x1 > checkRect.x2) continue;
        if (entityRect.x2 < checkRect.x1) continue;
        if (entityRect.y1 > checkRect.y2) continue;
        if (entityRect.y2 < checkRect.y1) continue;

        // Push entity
        lstEntity.Push(it->data);
    }
}
