#include <cmath>
#include "Game/Game.h"
#include "Game/Actor.h"
#include "Engine/CollisionManager.h"
#include "AI/GotoEntityTask.h"

static constexpr f32 ERROR_MULTIPLIER = 10.0f;
static constexpr f32 DECISION_RATIO_XY = 4.0f;

void GotoEntityTask::Handle()
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

    if (!g_game.GetWorld().HasEntity(m_pEntity))
    {
        m_status = AITASK_IMPOSSIBLE;
        return;
    }

    HandleActor();
}

b32 GotoEntityTask::IsDone()
{
    TList<Entity*> lstEntity;
    g_collisionMgr.CheckCollision(
        m_pActor->m_vPosition,
        m_pActor->m_hitBox,
        [] (auto pEntity, auto userdata) -> b32 { return pEntity == (Entity*)userdata; },
        m_pEntity,
        lstEntity
    );

    return !lstEntity.IsEmpty();
}

void GotoEntityTask::HandleActor()
{
    // Get positions and compute error
    const Vector2& vActor = m_pActor->m_vPosition;
    const Vector2& vEntity = m_pEntity->m_vPosition;
    Vector2 vError = { m_pActor->m_vSpeed.x * ERROR_MULTIPLIER,
                       m_pActor->m_vSpeed.y * ERROR_MULTIPLIER };

    // Move Actor according to x/y ratio
    f32 ratio = fabsf((vEntity.x - vActor.x) / (vEntity.y - vActor.y));
    if (ratio > DECISION_RATIO_XY)
    {
        MoveX(vActor, vEntity, vError);
    }
    else if (ratio < 1/DECISION_RATIO_XY)
    {
        MoveY(vActor, vEntity, vError);
    }
    else
    {
        MoveX(vActor, vEntity, vError);
        MoveY(vActor, vEntity, vError);
    }
}

void GotoEntityTask::MoveX(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError)
{
    if (vEntity.x < vActor.x - vError.x)
    {
        m_pActor->PushCommand(AICMD_MOVE_LEFT);
    }
    else if (vEntity.x > vActor.x + vError.x)
    {
        m_pActor->PushCommand(AICMD_MOVE_RIGHT);
    }
}

void GotoEntityTask::MoveY(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError)
{
    if (vEntity.y < vActor.y - vError.y)
    {
        m_pActor->PushCommand(AICMD_MOVE_UP);
    }
    else if (vEntity.y > vActor.y + vError.y)
    {
        m_pActor->PushCommand(AICMD_MOVE_DOWN);
    }
}
