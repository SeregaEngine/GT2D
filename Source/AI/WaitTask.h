#pragma once

#include "SDL.h"
#include "AI/GTTask.h"

class WaitTask final : public GT_Task
{
    f32 m_wait;

public:
    WaitTask(Actor* pActor, f32 wait) : GT_Task(pActor, GTT_WAIT), m_wait(wait) {}

    virtual void Handle() override;
};

