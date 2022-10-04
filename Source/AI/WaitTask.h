#ifndef WAITTASK_H_
#define WAITTASK_H_

/* ====== INCLUDES ====== */
#include "SDL.h"

#include "GTTask.h"

/* ====== STRUCTURES ====== */
class WaitTask final : public GT_Task
{
    u32 m_wait;
public:
    WaitTask(Actor* pActor, u32 wait)
        : GT_Task(pActor, GTT_WAIT), m_wait(SDL_GetTicks() + wait) {}

    virtual void Handle() override;
};


#endif // WAITTASK_H_