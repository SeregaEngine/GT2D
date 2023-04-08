#pragma once

#include "AI/AITask.h"

class KillTask final : public AITask
{
    Actor* m_pTarget;

public:
    KillTask(Actor* pActor, Actor* pTarget) : AITask(pActor, AITASK_KILL), m_pTarget(pTarget) {}

    virtual void Handle() override;

private:
    b32 IsDone() const;
    b32 IsPossible() const;
    void HandleActor();
};
