/* ====== TODO ======
 * - Timestamp
 * - Filter
 * - Verbosity
 * - Enable, disable console
 */

/* ====== INCLUDES ====== */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "DebugLogManager.h"

/* ====== VARIABLES ====== */
DebugLogManager g_debugLogMgr;

/* ====== DEFINES ====== */
#define NOTE_PREFIX_BUFSIZE  64
#define NOTE_MESSAGE_BUFSIZE 512
#define NOTE_FINAL_BUFSIZE   1024

#define PRIORITY_PREFIX_UNDEFINED "Undefined"
#define PRIORITY_PREFIX_ERROR     "Error"
#define PRIORITY_PREFIX_WARNING   "Warning"
#define PRIORITY_PREFIX_NOTE      "Note"

#define DIR_LOGS "Logs\\"
#define LOGS_EXTENSION ".log"

#define FILENAME_LOGFULL         DIR_LOGS "LogFull" LOGS_EXTENSION
#define FILENAME_DEBUGLOGMANAGER DIR_LOGS "DebugLogManager" LOGS_EXTENSION
#define FILENAME_GT2D            DIR_LOGS "GT2D" LOGS_EXTENSION
#define FILENAME_GRAPHICSMODULE  DIR_LOGS "GraphicsModule" LOGS_EXTENSION
#define FILENAME_INPUTMODULE     DIR_LOGS "InputModule" LOGS_EXTENSION
#define FILENAME_SOUNDMODULE     DIR_LOGS "SoundModule" LOGS_EXTENSION
#define FILENAME_SCRIPTMODULE    DIR_LOGS "ScriptModule" LOGS_EXTENSION
#define FILENAME_GAME            DIR_LOGS "Game" LOGS_EXTENSION

enum eFgColor
{
    FG_BLACK = 0,
    FG_BLUE = 1,
    FG_GREEN = 2,
    FG_CYAN = 3,
    FG_RED = 4,
    FG_MAGENTA = 5,
    FG_BROWN = 6,
    FG_LIGHTGRAY = 7,
    FG_GRAY = 8,
    FG_LIGHTBLUE = 9,
    FG_LIGHTGREEN = 10,
    FG_LIGHTCYAN = 11,
    FG_LIGHTRED = 12,
    FG_LIGHTMAGENTA = 13,
    FG_YELLOW = 14,
    FG_WHITE = 15
};

enum eBgColor
{
    BG_NAVYBLUE = 16,
    BG_GREEN = 32,
    BG_TEAL = 48,
    BG_MAROON = 64,
    BG_PURPLE = 80,
    BG_OLIVE = 96,
    BG_SILVER = 112,
    BG_GRAY = 128,
    BG_BLUE = 144,
    BG_LIME = 160,
    BG_CYAN = 176,
    BG_RED = 192,
    BG_MAGENTA = 208,
    BG_YELLOW = 224,
    BG_WHITE = 240
};

enum eChannelColor
{
    CHANNEL_COLOR_FREE1 = FG_GRAY,
    CHANNEL_COLOR_FREE2 = FG_YELLOW,

    CHANNEL_COLOR_UNDEFINED = FG_LIGHTMAGENTA,
    CHANNEL_COLOR_LOGMGR    = FG_WHITE,
    CHANNEL_COLOR_GT2D      = FG_LIGHTBLUE,
    CHANNEL_COLOR_GRAPHICS  = FG_LIGHTGREEN,
    CHANNEL_COLOR_INPUT     = FG_LIGHTCYAN,
    CHANNEL_COLOR_SOUND     = FG_LIGHTRED,
    CHANNEL_COLOR_SCRIPT    = FG_YELLOW,
    CHANNEL_COLOR_GAME      = FG_BROWN
};

enum ePriorityColor
{
    PRIORITY_COLOR_UNDEFINED = BG_TEAL,
    PRIORITY_COLOR_ERROR     = BG_RED,
    PRIORITY_COLOR_WARNING   = BG_NAVYBLUE,
    PRIORITY_COLOR_NOTE      = 0,
};

/* ====== METHODS ====== */
b32 DebugLogManager::StartUp()
{
    // Allocate console
    if (!AllocConsole())
        return false;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Open all log files
    std::filesystem::create_directory(DIR_LOGS);
    
    if ( nullptr == (hLogFull = fopen(FILENAME_LOGFULL, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hLogMgr = fopen(FILENAME_DEBUGLOGMANAGER, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hGT2D = fopen(FILENAME_GT2D, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hGraphics = fopen(FILENAME_GRAPHICSMODULE, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hInput = fopen(FILENAME_INPUTMODULE, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hSound = fopen(FILENAME_SOUNDMODULE, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if (nullptr == (hScript = fopen(FILENAME_SCRIPTMODULE, "w")))
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hGame = fopen(FILENAME_GAME, "w")) )
        AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));

    AddNote(CHANNEL_LOGMGR, PR_NOTE, "DebugLogManager", "Manager started");

    return true;
}

void DebugLogManager::ShutDown()
{
    AddNote(CHANNEL_LOGMGR, PR_NOTE, "DebugLogManager", "Manager shut down");

    // Close log files
    fclose(hLogFull);
    fclose(hLogMgr);
    fclose(hGT2D);
    fclose(hInput);
    fclose(hSound);
    fclose(hGraphics);
    fclose(hScript);
    fclose(hGame);

    // Detach console
    FreeConsole();
}

void DebugLogManager::VAddNote(s32 channel, s32 priority, const char* name, const char* fmt, va_list vl)
{
    FILE* hFile;
    const char* priorityName = "";
    WORD noteColor = 0;

    // Foreground color and channel prefix
    switch (channel)
    {

    case CHANNEL_LOGMGR:
    {
        hFile = hLogMgr;
        noteColor |= CHANNEL_COLOR_LOGMGR;
    } break;

    case CHANNEL_GT2D:
    {
        hFile = hGT2D;
        noteColor |= CHANNEL_COLOR_GT2D;
    } break;

    case CHANNEL_GRAPHICS:
    {
        hFile = hGraphics;
        noteColor |= CHANNEL_COLOR_GRAPHICS;
    } break;

    case CHANNEL_INPUT:
    {
        hFile = hInput;
        noteColor |= CHANNEL_COLOR_INPUT;
    } break;

    case CHANNEL_SOUND:
    {
        hFile = hSound;
        noteColor |= CHANNEL_COLOR_SOUND;
    } break;

    case CHANNEL_SCRIPT:
    {
        hFile = hScript;
        noteColor |= CHANNEL_COLOR_SCRIPT;
    } break;

    case CHANNEL_GAME:
    {
        hFile = hGame;
        noteColor |= CHANNEL_COLOR_GAME;
    } break;

    default:
    {
        hFile = nullptr;
        noteColor |= CHANNEL_COLOR_UNDEFINED;
    } break;

    }

    // Background color and priority prefix
    switch (priority)
    {
    case PR_ERROR:
    {
        priorityName = PRIORITY_PREFIX_ERROR;
        noteColor |= PRIORITY_COLOR_ERROR;
    } break;

    case PR_WARNING:
    {
        priorityName = PRIORITY_PREFIX_WARNING;
        noteColor |= PRIORITY_COLOR_WARNING;
    } break;

    case PR_NOTE:
    {
        priorityName = PRIORITY_PREFIX_NOTE;
        noteColor |= PRIORITY_COLOR_NOTE;
    } break;

    default:
    {
        priorityName = PRIORITY_PREFIX_UNDEFINED;
        noteColor |= PRIORITY_COLOR_UNDEFINED;
    } break;

    }

    // Get note prefix
    char notePrefix[NOTE_PREFIX_BUFSIZE];
    snprintf(notePrefix, NOTE_PREFIX_BUFSIZE, "<%s> %s", name, priorityName);

    // Get note message
    char noteMessage[NOTE_MESSAGE_BUFSIZE];
    vsnprintf(noteMessage, NOTE_MESSAGE_BUFSIZE, fmt, vl);

    // Get final note
    char noteFinal[NOTE_FINAL_BUFSIZE];
    snprintf(noteFinal, NOTE_FINAL_BUFSIZE, "%s: %s\n", notePrefix, noteMessage);
    size_t noteLength = strlen(noteFinal);

    // Output
    SetConsoleTextAttribute(hConsole, noteColor);
    WriteConsoleA(hConsole, noteFinal, (DWORD)noteLength, NULL, NULL);

    fwrite(noteFinal, 1, noteLength, hLogFull);
    if (hFile)
        fwrite(noteFinal, 1, noteLength, hFile);

    // Flush stuff
    fflush(hLogFull);
    fflush(hFile);
}

void DebugLogManager::AddNote(s32 channel, s32 priority, const char* name, const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);

    VAddNote(channel, priority, name, fmt, vl);

    va_end(vl);
}
