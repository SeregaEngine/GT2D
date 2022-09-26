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
};

#endif // KILLTASK_H_