#ifndef WAITTASK_H_
#define WAITTASK_H_

/* ====== INCLUDES ====== */
#include "SDL.h"

#include "GTTask.h"

/* ====== STRUCTURES ====== */
class WaitTask final : public GT_Task
{
    f32 m_wait;
public:
    WaitTask(Actor* pActor, f32 wait)
        : GT_Task(pActor, GTT_WAIT), m_wait(wait) {}

    virtual void Handle() override;
};


#endif // WAITTASK_H_