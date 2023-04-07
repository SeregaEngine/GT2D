#pragma once

#include "AI/WaitTask.h"
#include "Game/Actor.h"

struct Animation;

class AnimateForTask final : public AITask
{
    WaitTask* m_pWaitTask;

public:
    AnimateForTask(Actor* pActor, const Animation* pAnim, f32 wait) :
        AITask(pActor, AITASK_ANIMATE_FOR), m_pWaitTask(new WaitTask(pActor, wait))
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
        if (m_status != AITASK_INPROCESS)
        {
            return;
        }

        m_pWaitTask->Handle();

        s32 waitStatus = m_pWaitTask->GetStatus();
        if (waitStatus == AITASK_DONE || waitStatus == AITASK_IMPOSSIBLE)
        {
            m_pActor->m_actorState = ACTOR_STATE_AFTER_ANIMATION;
            m_status = waitStatus;
        }
    }
};
