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

b32 KillTask::IsDone()
{
    if (!g_game.GetWorld().HasEntity(m_pTarget) || m_pTarget->m_actorState == ACTOR_STATE_DEAD)
        return true;
    return false;
}

b32 KillTask::IsPossible()
{
    // Check if we are near the target
    TList<Entity*> lstEntity;
    g_collisionMgr.CheckCollision(m_pActor->m_vPosition, m_pActor->m_hitBox, [](auto pEntity, auto userdata) -> b32 {
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
    if (m_pTarget->m_vPosition.x < m_pActor->m_vPosition.x)
        m_pActor->m_bLookRight = false;
    else
        m_pActor->m_bLookRight = true;

    m_pActor->SendCommand(GTC_ATTACK);
}
