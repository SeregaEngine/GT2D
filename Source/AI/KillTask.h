#pragma once

#include "GTTask.h"

class KillTask final : public GT_Task
{
    Actor* m_pTarget;

public:
    KillTask(Actor* pActor, Actor* pTarget) : GT_Task(pActor, GTT_KILL), m_pTarget(pTarget) {}

    virtual void Handle() override;

private:
    b32 IsDone();
    b32 IsPossible();
    void HandleActor();
};
