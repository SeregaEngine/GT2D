#ifndef KILLTASK_H_
#define KILLTASK_H_

/* ====== INCLUDES ====== */
#include "GTTask.h"

/* ====== STRUCTURES ====== */
class KillTask final : public GT_Task
{
    Actor* m_pTarget;
public:
    KillTask(Actor* pActor, Actor* pTarget)
        : GT_Task(pActor, GTT_KILL), m_pTarget(pTarget) {}

    virtual void Handle() override;
private:
    b32f IsDone();
    b32f IsPossible();
    void HandleActor();
};

#endif // KILLTASK_H_