/* ====== INCLUDES ====== */
#include "WaitTask.h"

/* ====== METHODS ====== */
void WaitTask::Handle()
{
    if (SDL_GetTicks() >= m_wait)
        m_status = GTT_DONE;
}
