/* ====== INCLUDES ====== */
#include "Game.h"

#include "CollisionManager.h"

/* ====== METHODS ====== */
b32 CollisionManager::StartUp()
{
    AddNote(PR_NOTE, "Module started");

    return true;
}

void CollisionManager::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

b32 CollisionManager::IsOnGround(const Vector2& vPoint, const FRect& hitBox) const
{
    const SRect& ground = g_game.GetWorld().GetGroundBounds();

    if (vPoint.y + hitBox.y2 >= ground.y1 && vPoint.y + hitBox.y2 <= ground.y2 &&
        vPoint.x + hitBox.x1 >= ground.x1 && vPoint.x + hitBox.x2 <= ground.x2)
        return true;
    return false;
}

void CollisionManager::CheckCollision(const Vector2& vPoint, const FRect& hitBox, TList<Entity*>& lstEntity, const Entity* pExcept) const
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
        if (it->data == pExcept || !it->data->m_bCollidable)
            continue;

        // Get entity hitbox in world coords
        const Vector2& vEntity = it->data->m_vPosition;
        const FRect& entityBox = it->data->m_hitBox;
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

void CollisionManager::CheckCollision(const Vector2& vPoint, const FRect& hitBox, b32 (*predicate)(Entity*, void*), void* userdata, TList<Entity*>& lstEntity, const Entity* pExcept) const
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
        if (it->data == pExcept || !it->data->m_bCollidable || !predicate(it->data, userdata))
            continue;

        // Get entity hitbox in world coords
        const Vector2& vEntity = it->data->m_vPosition;
        const FRect& entityBox = it->data->m_hitBox;
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
