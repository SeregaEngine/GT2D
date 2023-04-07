#pragma once

#include "AI/AITask.h"
#include "Game/Actor.h"

class PushCommandTask final : public AITask
{
public:
    PushCommandTask(Actor* pActor, s32 enumCommand) : AITask(pActor, AITASK_PUSH_COMMAND)
    {
        if (pActor)
        {
            pActor->PushCommand(enumCommand);
        }
        m_status = AITASK_DONE;
    }
};

