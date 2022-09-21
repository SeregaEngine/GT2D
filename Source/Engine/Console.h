#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "EngineModule.h"

class Console : public EngineModule
{
    u8* m_buffer;
    b32 m_bShown;
public:
    Console() : EngineModule("Console", CHANNEL_LOGMGR) {}

    b32f StartUp();
    void ShutDown();

    void Render() const {}

    void Toggle(b32 bToggle) { m_bShown = bToggle; }
    b32 IsShown() const { return m_bShown; }

    void Print(const char* text) {}
    void Input(i32f ch) { AddNote(PR_NOTE, "%c", ch); }
    void Interpret() { AddNote(PR_NOTE, "Interpreted"); }
};

extern Console g_console;

#endif // CONSOLE_H_
