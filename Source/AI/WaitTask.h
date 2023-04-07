#pragma once

#include "SDL.h"
#include "AI/AITask.h"

class WaitTask final : public AITask
{
    f32 m_wait;

public:
    WaitTask(Actor* pActor, f32 wait) : AITask(pActor, AITASK_WAIT), m_wait(wait) {}

    virtual void Handle() override;
};

