#pragma once

#include "Engine/Types.h"
#include "Engine/Platform.h"
#include "Engine/DebugLogManager.h"

class EngineModule
{
    const char* m_moduleName;
    s32 m_moduleChannel;

protected:
    void AddNote(s32 priority, const char* fmt, ...) const;

public:
    EngineModule(const char* name, s32 channel) : m_moduleName(name), m_moduleChannel(channel) {}
    virtual ~EngineModule() = default;

    forceinline const char* GetModuleName() const { return m_moduleName; }
    forceinline s32 GetModuleChannel() const { return m_moduleChannel; }
};
