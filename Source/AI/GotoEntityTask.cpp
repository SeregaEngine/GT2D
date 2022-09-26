/* ====== INCLUDES ====== */
#include <math.h>

#include "Game.h"
#include "Actor.h"
#include "CollisionManager.h"

#include "GotoEntityTask.h"

/* ====== DEFINES ====== */
#define ERROR_MULTIPLIER 7.5f
#define DECISION_RATIO_XY 2.0f

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
    // Get positions and compute error
    const Vector2& vActor = m_pActor->GetPosition();
    const Vector2& vEntity = m_pEntity->GetPosition();
    Vector2 vError = { m_pActor->GetSpeed().x * ERROR_MULTIPLIER,
                       m_pActor->GetSpeed().y * ERROR_MULTIPLIER };

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
    // X
    if (vEntity.x < vActor.x - vError.x)
        m_pActor->SendCommand(GTC_MOVE_LEFT);
    else if (vEntity.x > vActor.x + vError.x)
        m_pActor->SendCommand(GTC_MOVE_RIGHT);
}

void GotoEntityTask::MoveY(const Vector2& vActor, const Vector2& vEntity, const Vector2& vError)
{
    // Y
    if (vEntity.y < vActor.y - vError.y)
        m_pActor->SendCommand(GTC_MOVE_UP);
    else if (vEntity.y > vActor.y + vError.y)
        m_pActor->SendCommand(GTC_MOVE_DOWN);
}
