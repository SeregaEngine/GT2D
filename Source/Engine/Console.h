#pragma once

#include "EngineModule.h"

class Console : public EngineModule
{
    u8* m_buffer;
    u8* m_lastInput;
    b32 m_bShown;

    s32 m_currentRow;     /** Row for Print() */
    s32 m_currentInput;   /** Last position in input's row */
    s32 m_cursorPosition; /** Cursor's position */

    s32 m_lastInputPosition;
    s32 m_lastCursorPosition;

public:
    Console() : EngineModule("Console", CHANNEL_LOGMGR) {}

    b32 StartUp();
    void ShutDown();

    void Render() const;

    void Toggle(b32 bToggle) { m_bShown = bToggle; }
    b32 IsShown() const { return m_bShown; }

    void Print(const char* text);
    void Input(i32f ch);
    void Clear();

private:
    void Arrow(i32f ch);
    void Interpret();

    void LineFeed();
    void Erase();
    void Reset();
};

inline Console g_console;
