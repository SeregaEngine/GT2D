/* ====== INCLUDES ====== */
#include "KillTask.h"

/* ====== METHODS ====== */
void KillTask::Handle()
{
    if (m_status != GTT_INPROCESS)
        return;

    m_status = GTT_DONE;
}
