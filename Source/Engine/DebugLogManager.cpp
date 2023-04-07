#include <cstdlib>
#include <cerrno>
#include <cstdarg>
#include <filesystem>
#include "Engine/Console.h"
#include "Engine/DebugLogManager.h"
#include "Engine/Assert.h"

static constexpr i32f NOTE_PREFIX_BUFSIZE  = 64;
static constexpr i32f NOTE_MESSAGE_BUFSIZE = 512;
static constexpr i32f NOTE_FINAL_BUFSIZE   = 1024;

static constexpr char PRIORITY_PREFIX_UNDEFINED[] = "Undefined";
static constexpr char PRIORITY_PREFIX_ERROR[]     = "Error";
static constexpr char PRIORITY_PREFIX_WARNING[]   = "Warning";
static constexpr char PRIORITY_PREFIX_NOTE[]      = "Note";

#define DIR_LOGS "Logs\\"
#define LOGS_EXTENSION ".log"

static constexpr char FILENAME_LOGFULL[]         = DIR_LOGS "LogFull" LOGS_EXTENSION;
static constexpr char FILENAME_DEBUGLOGMANAGER[] = DIR_LOGS "DebugLogManager" LOGS_EXTENSION;
static constexpr char FILENAME_GT2D[]            = DIR_LOGS "GT2D" LOGS_EXTENSION;
static constexpr char FILENAME_GRAPHICSMODULE[]  = DIR_LOGS "GraphicsModule" LOGS_EXTENSION;
static constexpr char FILENAME_INPUTMODULE[]     = DIR_LOGS "InputModule" LOGS_EXTENSION;
static constexpr char FILENAME_SOUNDMODULE[]     = DIR_LOGS "SoundModule" LOGS_EXTENSION;
static constexpr char FILENAME_ANIMATIONMODULE[] = DIR_LOGS "AnimationModule" LOGS_EXTENSION;
static constexpr char FILENAME_SCRIPTMODULE[]    = DIR_LOGS "ScriptModule" LOGS_EXTENSION;
static constexpr char FILENAME_GAME[]            = DIR_LOGS "Game" LOGS_EXTENSION;

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
    CHANNEL_COLOR_UNDEFINED = FG_LIGHTMAGENTA,
    CHANNEL_COLOR_LOGMGR    = FG_WHITE,
    CHANNEL_COLOR_GT2D      = FG_LIGHTBLUE,
    CHANNEL_COLOR_GRAPHICS  = FG_LIGHTGREEN,
    CHANNEL_COLOR_INPUT     = FG_LIGHTCYAN,
    CHANNEL_COLOR_SOUND     = FG_LIGHTRED,
    CHANNEL_COLOR_ANIMATION = FG_GRAY,
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

void DebugLogManager::StartUp()
{
#ifdef _DEBUG
    // Allocate windows console
    b32 bRes = AllocConsole();
    DebugAssert(bRes);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    // Start up engine's console
    g_console.StartUp();

    // Open all log files
    std::filesystem::create_directory(DIR_LOGS);

    hLogFull = fopen(FILENAME_LOGFULL, "w");
    ShipAssert(hLogFull);

    if ( nullptr == (hLogMgr = fopen(FILENAME_DEBUGLOGMANAGER, "w")) )  AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hGT2D = fopen(FILENAME_GT2D, "w")) )               AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hGraphics = fopen(FILENAME_GRAPHICSMODULE, "w")) ) AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hInput = fopen(FILENAME_INPUTMODULE, "w")) )       AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hSound = fopen(FILENAME_SOUNDMODULE, "w")) )       AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hAnim = fopen(FILENAME_ANIMATIONMODULE, "w")) )    AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hScript = fopen(FILENAME_SCRIPTMODULE, "w")) )     AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));
    if ( nullptr == (hGame = fopen(FILENAME_GAME, "w")) )               AddNote(CHANNEL_LOGMGR, PR_WARNING, "DebugLogManager", "Can't open log file: %s", strerror(errno));

    AddNote(CHANNEL_LOGMGR, PR_NOTE, "DebugLogManager", "Manager started");
}

void DebugLogManager::ShutDown()
{
    AddNote(CHANNEL_LOGMGR, PR_NOTE, "DebugLogManager", "Manager shut down");

    // Close log files
    fclose(hLogFull);
    fclose(hLogMgr);
    fclose(hGT2D);
    fclose(hGraphics);
    fclose(hInput);
    fclose(hSound);
    fclose(hAnim);
    fclose(hScript);
    fclose(hGame);

    // Detach consoles
    g_console.ShutDown();
#ifdef _DEBUG
    FreeConsole();
#endif
}

void DebugLogManager::VAddNote(s32 channel, s32 priority, const char* name, const char* fmt, std::va_list vl)
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

    case CHANNEL_ANIMATION:
    {
        hFile = hAnim;
        noteColor |= CHANNEL_COLOR_ANIMATION;
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
    size_t noteLength = std::strlen(noteFinal);

    // Output
    g_console.Print(noteFinal);

    SetConsoleTextAttribute(hConsole, noteColor);
    WriteConsoleA(hConsole, noteFinal, (DWORD)noteLength, nullptr, nullptr);

    fwrite(noteFinal, 1, noteLength, hLogFull);
    if (hFile)
    {
        fwrite(noteFinal, 1, noteLength, hFile);
    }

    // Flush stuff
    fflush(hLogFull);
    fflush(hFile);
}

void DebugLogManager::AddNote(s32 channel, s32 priority, const char* name, const char* fmt, ...)
{
    std::va_list vl;
    va_start(vl, fmt);

    VAddNote(channel, priority, name, fmt, vl);

    va_end(vl);
}
