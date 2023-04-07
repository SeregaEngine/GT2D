#pragma once

#include "AI/AITask.h"
#include "Math/Math.h"

class GotoTask final : public AITask
{
    Vector2 m_vDestination;
    b32 m_bCompletedX, m_bCompletedY;

public:
    GotoTask(Actor* pActor, const Vector2& vDestination) :
        AITask(pActor, AITASK_GOTO), m_vDestination(vDestination),
        m_bCompletedX(false), m_bCompletedY(false) {}

    virtual void Handle() override;
};