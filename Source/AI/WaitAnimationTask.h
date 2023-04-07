#pragma once

#include "Game/Actor.h"

struct Animation;

class WaitAnimationTask final : public AITask
{
public:
    WaitAnimationTask(Actor* pActor, const Animation* pAnim) : AITask(pActor, AITASK_ANIMATE_FOR)
    {
        pActor->m_pAnim = pAnim ? pAnim : pActor->m_aActorAnims[ACTOR_ANIMATION_IDLE];
        pActor->m_animFrame = 0;
        pActor->m_animElapsed = 0.0f;
        pActor->m_actorState = ACTOR_STATE_ANIMATE_ONCE;
    }

    virtual void Handle() override
    {
        if (m_status != AITASK_INPROCESS)
        {
            return;
        }

        if (m_pActor->m_actorState != ACTOR_STATE_ANIMATE_ONCE)
        {
            m_status = AITASK_DONE;
        }
    }
};

