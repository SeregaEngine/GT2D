#pragma once

#include "Engine/Types.h"

enum eGT_TaskStatus
{
    GTT_INPROCESS = 1,
    GTT_IMPOSSIBLE = 2,
    GTT_DONE = 3,

    GTT_STATUS_END
};

enum eGT_TaskID
{
    GTT_TASK_START = GTT_STATUS_END,

    GTT_NONE = 0,
    GTT_WAIT = GTT_TASK_START,
    GTT_GOTO,
    GTT_GOTO_ENTITY,
    GTT_KILL,
    GTT_ANIMATE_FOR,
    GTT_WAIT_ANIMATION,
    GTT_WAIT_DIALOG,
    GTT_WAIT_TALKING,
    GTT_RUN_DIALOG,
    GTT_FADE_IN,
    GTT_FADE_OFF,
    GTT_PUSH_COMMAND,
};

class Actor;

/**
 * Tasks send commands to Actors
 */
class GT_Task
{
protected:
    Actor* m_pActor;
    s32 m_id;
    s32 m_status;

public:
    GT_Task(Actor* pActor, s32 id) : m_pActor(pActor), m_id(id), m_status(GTT_INPROCESS) {}
    virtual ~GT_Task() = default;

    s32 GetID() const { return m_id; }
    s32 GetStatus() const { return m_status; }

    virtual void Handle() {}
};