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

b32f CollisionManager::IsOnGround(const Vector2& vPoint, const FRect& hitBox)
{
    const SRect& ground = g_game.GetWorld().GetGroundBounds();

    if (vPoint.y + hitBox.y2 >= ground.y1 && vPoint.y + hitBox.y2 <= ground.y2 &&
        vPoint.x + hitBox.x1 >= ground.x1 && vPoint.x + hitBox.x2 <= ground.x2)
        return true;
    return false;
}

void CollisionManager::GetCollidedEntities(const Vector2& vPoint, const FRect& hitBox, TList<Entity*>& lstEntity) const
{

}
