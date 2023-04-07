#include "DebugLogManager.h"
#include "EngineModule.h"

void EngineModule::AddNote(s32 priority, const char* fmt, ...) const
{
    va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(m_moduleChannel, priority, m_moduleName, fmt, vl);
    va_end(vl);
}
