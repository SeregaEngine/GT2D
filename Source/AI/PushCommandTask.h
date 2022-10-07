#ifndef PUSHCOMMANDTASK_H_
#define PUSHCOMMANDTASK_H_

/* ====== INCLUDES ====== */
#include "GTTask.h"
#include "Actor.h"

/* ====== STRUCTURES ====== */
class PushCommandTask final : public GT_Task
{
public:
    PushCommandTask(Actor* pActor, s32 enumCommand) : GT_Task(pActor, GTT_PUSH_COMMAND)
        { if (pActor) pActor->PushCommand(enumCommand); m_status = GTT_DONE; }

    virtual void Handle() override {}
};

#endif // PUSHCOMMANDTASK_H_
