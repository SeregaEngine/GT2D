#include "Engine/ClockManager.h"
#include "AI/WaitTask.h"

void WaitTask::Handle()
{
    m_wait -= g_clockMgr.GetDelta();
    if (m_wait <= 0.0f)
    {
        m_status = GTT_DONE;
    }
}
