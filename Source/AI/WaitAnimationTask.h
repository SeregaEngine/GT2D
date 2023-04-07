#pragma once

#include "Game/Actor.h"

struct GT_Animation;

class WaitAnimationTask final : public GT_Task
{
public:
    WaitAnimationTask(Actor* pActor, const GT_Animation* pAnim) : GT_Task(pActor, GTT_ANIMATE_FOR)
    {
        pActor->m_pAnim = pAnim ? pAnim : pActor->m_aActorAnims[ACTOR_ANIMATION_IDLE];
        pActor->m_animFrame = 0;
        pActor->m_animElapsed = 0.0f;
        pActor->m_actorState = ACTOR_STATE_ANIMATE_ONCE;
    }

    virtual void Handle() override
    {
        if (m_status != GTT_INPROCESS)
        {
            return;
        }

        if (m_pActor->m_actorState != ACTOR_STATE_ANIMATE_ONCE)
        {
            m_status = GTT_DONE;
        }
    }
};

