#pragma once

#include "Engine/Types.h"

enum eAITaskStatus
{
    AITASK_INPROCESS = 1,
    AITASK_IMPOSSIBLE = 2,
    AITASK_DONE = 3,

    AITASK_STATUS_END
};

enum eAITaskID
{
    AITASK_TASK_START = AITASK_STATUS_END,

    AITASK_NONE = 0,
    AITASK_WAIT = AITASK_TASK_START,
    AITASK_GOTO,
    AITASK_GOTO_ENTITY,
    AITASK_KILL,
    AITASK_ANIMATE_FOR,
    AITASK_WAIT_ANIMATION,
    AITASK_WAIT_DIALOG,
    AITASK_WAIT_TALKING,
    AITASK_RUN_DIALOG,
    AITASK_FADE_IN,
    AITASK_FADE_OFF,
    AITASK_PUSH_COMMAND,
};

class Actor;

/**
 * Tasks send commands to Actors
 */
class AITask
{
protected:
    Actor* m_pActor;
    s32 m_id;
    s32 m_status;

public:
    AITask(Actor* pActor, s32 id) : m_pActor(pActor), m_id(id), m_status(AITASK_INPROCESS) {}
    virtual ~AITask() = default;

    forceinline s32 GetID() const { return m_id; }
    forceinline s32 GetStatus() const { return m_status; }

    virtual void Handle() {}
};