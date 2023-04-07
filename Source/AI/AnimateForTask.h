#pragma once

#include "WaitTask.h"
#include "Actor.h"

struct GT_Animation;

class AnimateForTask final : public GT_Task
{
    WaitTask* m_pWaitTask;

public:
    AnimateForTask(Actor* pActor, const GT_Animation* pAnim, f32 wait) :
        GT_Task(pActor, GTT_ANIMATE_FOR), m_pWaitTask(new WaitTask(pActor, wait))
    {
        pActor->m_pAnim = pAnim ? pAnim : pActor->m_aActorAnims[ACTOR_ANIMATION_IDLE];
        pActor->m_animFrame = 0;
        pActor->m_animElapsed = 0.0f;
        pActor->m_actorState = ACTOR_STATE_ANIMATE_LOOPED;
    }

    ~AnimateForTask()
    {
        if (m_pWaitTask)
        {
            delete m_pWaitTask;
        }
    }

    virtual void Handle() override
    {
        if (m_status != GTT_INPROCESS)
        {
            return;
        }

        m_pWaitTask->Handle();

        s32 waitStatus = m_pWaitTask->GetStatus();
        if (waitStatus == GTT_DONE || waitStatus == GTT_IMPOSSIBLE)
        {
            m_pActor->m_actorState = ACTOR_STATE_AFTER_ANIMATION;
            m_status = waitStatus;
        }
    }
};
