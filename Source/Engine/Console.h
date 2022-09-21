#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "EngineModule.h"

class Console : public EngineModule
{
    u8* m_buffer;
    b32 m_bShown;

    s32 m_currentRow;   // Row for Print()
    s32 m_currentInput; // Position in input's row
public:
    Console() : EngineModule("Console", CHANNEL_LOGMGR) {}

    b32f StartUp();
    void ShutDown();

    void Render() const;

    void Toggle(b32 bToggle) { m_bShown = bToggle; }
    b32 IsShown() const { return m_bShown; }

    void Print(const char* text);
    void Input(i32f ch);
    void Interpret();

    void Clear();
    void Reset();

private:
    void LineFeed();
    void Erase();
};

extern Console g_console;

#endif // CONSOLE_H_
