#include "Engine/DebugLogManager.h"
#include "Engine/EngineModule.h"

void EngineModule::AddNote(s32 priority, const char* fmt, ...) const
{
    std::va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(m_moduleChannel, priority, m_moduleName, fmt, vl);
    va_end(vl);
}
