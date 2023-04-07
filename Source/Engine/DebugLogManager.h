#pragma once

#include <cstdio>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Engine/Types.h"

/** Each channel represent engine's module */
enum eDebugLogChannel
{
    CHANNEL_LOGMGR    = 1 << 0,
    CHANNEL_GT2D      = 1 << 1,
    CHANNEL_GRAPHICS  = 1 << 4,
    CHANNEL_INPUT     = 1 << 5,
    CHANNEL_SOUND     = 1 << 6,
    CHANNEL_ANIMATION = 1 << 7,
    CHANNEL_SCRIPT    = 1 << 8,
    CHANNEL_GAME      = 1 << 9
};

enum eDebugLogPriority
{
    PR_ERROR   = 1 << 0,
    PR_WARNING = 1 << 1,
    PR_NOTE    = 1 << 2
};

class DebugLogManager
{
    HANDLE hConsole;
    FILE* hLogFull;

    FILE* hLogMgr;
    FILE* hGT2D;
    FILE* hGraphics;
    FILE* hInput;
    FILE* hSound;
    FILE* hAnim;
    FILE* hScript;
    FILE* hGame;

public:
    b32 StartUp();
    void ShutDown();

    void AddNote(s32 channel, s32 priority, const char* name, const char* fmt, ...);
    void VAddNote(s32 channel, s32 priority, const char* name, const char* fmt, va_list vl);
};

inline DebugLogManager g_debugLogMgr;
