#ifndef ENGINEMODULE_H_
#define ENGINEMODULE_H_

/* ====== INCLUDES ====== */
#include "Types.h"
#include "DebugLogManager.h"

/* ====== STRUCTURES ====== */
class EngineModule
{
    const char* m_moduleName;
    s32 m_moduleChannel;

protected:
    void AddNote(s32 priority, const char* fmt, ...) const;
public:
    EngineModule(const char* name, s32 channel)
        : m_moduleName(name), m_moduleChannel(channel) {}
    virtual ~EngineModule() {}

    const char* GetModuleName() const { return m_moduleName; }
    s32 GetModuleChannel() const { return m_moduleChannel; }
};

#endif // ENGINEMODULE_H_
