#ifndef GTTASK_H_
#define GTTASK_H_

/* ====== INCLUDES ====== */
#include <Types.h>

/* ====== DEFINES ====== */
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
    GTT_GOTO = GTT_TASK_START,
    GTT_GOTO_ENTITY,
    GTT_KILL,
};

/* ====== STRUCTURES ====== */
class Actor;

// Tasks send commands to Actors
class GT_Task
{
protected:
    Actor* m_pActor;
    s32 m_id;
    s32 m_status;
public:
    GT_Task(Actor* pActor, s32 id) : m_pActor(pActor), m_id(id), m_status(GTT_INPROCESS) {}
    virtual ~GT_Task() {}

    s32 GetID() const { return m_id; }
    s32 GetStatus() const { return m_status; }

    virtual void Handle() = 0;
};

#endif // GTTASK_H_