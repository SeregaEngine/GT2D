#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "EngineModule.h"

class Console : public EngineModule
{
    u8* m_buffer;
    u8* m_lastInput;
    b32 m_bShown;

    s32 m_currentRow;   // Row for Print()
    s32 m_currentInput; // Last position in input's row
    s32 m_cursorPosition; // Cursor's position
    s32 m_lastCursorPosition;
public:
    Console() : EngineModule("Console", CHANNEL_LOGMGR) {}

    b32f StartUp();
    void ShutDown();

    void Render() const;

    void Toggle(b32 bToggle) { m_bShown = bToggle; }
    b32 IsShown() const { return m_bShown; }

    void Print(const char* text);
    void Interpret();

    void Input(i32f ch);
    void Clear();
    void Reset();

private:
    void Arrow(i32f ch);
    void LineFeed();
    void Erase();
};

extern Console g_console;

#endif // CONSOLE_H_
