#include "DebugLogManager.h"

#include "GotoTask.h"

void GotoTask::Handle()
{
    if (m_status != GTT_INPROCESS)
        return;

    g_debugLogMgr.AddNote(CHANNEL_GAME, PR_NOTE, "GotoTask", "%p: %p", this, m_pActor);
}
