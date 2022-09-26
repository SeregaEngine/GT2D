/* ====== INCLUDES ====== */
#include "Game.h"
#include "Actor.h"
#include "CollisionManager.h"

#include "GotoEntityTask.h"

/* ====== METHODS ====== */
void GotoEntityTask::Handle()
{
    if (m_status != GTT_INPROCESS)
        return;

    if (IsDone())
    {
        m_status = GTT_DONE;
        return;
    }

    if (!g_game.GetWorld().HasEntity(m_pEntity))
    {
        m_status = GTT_IMPOSSIBLE;
        return;
    }

    HandleActor();
}

b32f GotoEntityTask::IsDone()
{
    TList<Entity*> lstEntity;
    g_collisionMgr.CheckCollision(m_pActor->GetPosition(), m_pActor->GetHitBox(), [](auto pEntity, auto userdata) -> b32f {
        if (pEntity == (Entity*)userdata)
            return true;
        return false;
    }, m_pEntity, lstEntity);

    if (lstEntity.IsEmpty())
        return false;
    return true;
}

void GotoEntityTask::HandleActor()
{
    const Vector2& vActor = m_pActor->GetPosition();
    const Vector2& vEntity = m_pEntity->GetPosition();

    // TODO(sean) If we are near vEntity, don't do anything
    // X
    if (vEntity.x < vActor.x)
        m_pActor->SendCommand(GTC_MOVE_LEFT);
    else if (vEntity.x > vActor.x)
        m_pActor->SendCommand(GTC_MOVE_RIGHT);

    // Y
    if (vEntity.y < vActor.y)
        m_pActor->SendCommand(GTC_MOVE_UP);
    else if (vEntity.y > vActor.y)
        m_pActor->SendCommand(GTC_MOVE_DOWN);
}
