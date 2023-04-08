#include "Game/Game.h"
#include "Game/Actor.h"
#include "Engine/StdHeaders.h"
#include "Engine/CollisionManager.h"
#include "AI/KillTask.h"

static constexpr i32f ERROR_RATE = 300;

void KillTask::Handle()
{
    if (m_status != AITASK_INPROCESS)
    {
        return;
    }

    if (IsDone())
    {
        m_status = AITASK_DONE;
        return;
    }

    if (!IsPossible())
    {
        m_status = AITASK_IMPOSSIBLE;
        return;
    }

    HandleActor();
}

b32 KillTask::IsDone() const
{
    return !g_game.GetWorld().HasEntity(m_pTarget) || m_pTarget->m_actorState == ACTOR_STATE_DEAD;
}

b32 KillTask::IsPossible() const
{
    // Check if we are near the target
    TList<Entity*> lstEntity;
    g_collisionMgr.CheckCollision(
        m_pActor->m_vPosition,
        m_pActor->m_hitBox,
        [] (auto pEntity, auto userdata) -> b32 { return pEntity == (Entity*)userdata; },
        m_pTarget,
        lstEntity
    );

    // Impossible if there no target
    return !lstEntity.IsEmpty();
}

void KillTask::HandleActor()
{
    if (m_pTarget->m_vPosition.x < m_pActor->m_vPosition.x)
    {
        m_pActor->m_bLookRight = false;
    }
    else
    {
        m_pActor->m_bLookRight = true;
    }

    if (m_pActor->m_animElapsed - (f32)(std::rand() % ERROR_RATE) > m_pActor->m_attackRate)
    {
        m_pActor->PushCommand(AICMD_ATTACK);
    }
}
