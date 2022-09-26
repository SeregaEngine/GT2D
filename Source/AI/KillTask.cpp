/* ====== INCLUDES ====== */
#include "Game.h"
#include "Actor.h"
#include "CollisionManager.h"

#include "KillTask.h"

/* ====== METHODS ====== */
void KillTask::Handle()
{
    if (m_status != GTT_INPROCESS)
        return;

    if (IsDone())
    {
        m_status = GTT_DONE;
        return;
    }

    if (!IsPossible())
    {
        m_status = GTT_IMPOSSIBLE;
        return;
    }

    HandleActor();
}

b32f KillTask::IsDone()
{
    if (!g_game.GetWorld().HasEntity(m_pTarget) || m_pTarget->GetHealth() <= 0)
        return true;
    return false;
}

b32f KillTask::IsPossible()
{
    // Check if we are near the target
    TList<Entity*> lstEntity;
    g_collisionMgr.CheckCollision(m_pActor->GetPosition(), m_pActor->GetHitBox(), [](auto pEntity, auto userdata) -> b32f {
        if (pEntity == (Entity*)userdata)
            return true;
        return false;
    }, m_pTarget, lstEntity);

    // Impossible if there no target
    if (lstEntity.IsEmpty())
        return false;

    return true;
}

void KillTask::HandleActor()
{
    if (m_pTarget->GetPosition().x < m_pActor->GetPosition().x)
        m_pActor->TurnLeft();
    else
        m_pActor->TurnRight();

    m_pActor->SendCommand(GTC_ATTACK);
}
