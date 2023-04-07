#pragma once

#include "GTTask.h"
#include "Actor.h"

class PushCommandTask final : public GT_Task
{
public:
    PushCommandTask(Actor* pActor, s32 enumCommand) : GT_Task(pActor, GTT_PUSH_COMMAND)
    {
        if (pActor)
        {
            pActor->PushCommand(enumCommand);
        }
        m_status = GTT_DONE;
    }
};

