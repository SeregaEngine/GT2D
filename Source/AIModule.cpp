/* ====== INCLUDES ====== */
#include "DebugLogManager.h"

#include "AIModule.h"

/* ====== DEFINES ====== */

/* ====== VARIABLES ====== */
AIModule g_AIModule;

/* ====== METHODS ====== */
b32 AIModule::StartUp()
{
    AddNote(PR_NOTE, "Module start up");
    return true;
}

void AIModule::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

void AIModule::AddNote(s32 priority, const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(CHANNEL_SCRIPT, priority, "AIModule", fmt, vl);
    va_end(vl);
}