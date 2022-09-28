/* ====== INCLUDES ====== */
#include <string.h>

#include "GraphicsModule.h"
#include "ScriptModule.h"

#include "Console.h"

/* ====== DEFINES ====== */
#define CONSOLE_STRING_WIDTH 80
#define CONSOLE_STRING_HEIGHT 15
#define CONSOLE_BUFSIZE ((CONSOLE_STRING_WIDTH * CONSOLE_STRING_HEIGHT) + 1)

#define CONSOLE_INPUT_INDEX (CONSOLE_STRING_WIDTH * (CONSOLE_STRING_HEIGHT - 1))

#define LAST_BUFSIZE (CONSOLE_STRING_WIDTH + 1)

static const char s_consolePrompt[] = "> ";

/* ====== VARIABLES ====== */
Console g_console;

/* ====== METHODS ====== */
b32f Console::StartUp()
{
    // Allocate and init buffer
    m_buffer = new u8[CONSOLE_BUFSIZE];
    Clear();
    Reset();

    // Allocate and init last input buffer
    m_lastInput = new u8[CONSOLE_STRING_WIDTH + 1];
    memcpy(m_lastInput, &m_buffer[CONSOLE_INPUT_INDEX], LAST_BUFSIZE);

    // Defaults
    m_bShown = false;
    m_lastInputPosition = m_currentInput;
    m_lastCursorPosition = m_cursorPosition;

    return true;
}

void Console::ShutDown()
{
    delete[] m_buffer;
}

void Console::Render() const
{
    // Draw console's background
    g_graphicsModule.SetDrawColor(0x00, 0x00, 0x00, 0xFF);
    SDL_Rect dest = { 0, 0, g_graphicsModule.GetScreenWidth(),
                            g_graphicsModule.GetScreenHeight() / 2 };
    g_graphicsModule.FillRect(RENDER_MODE_DEBUG, 0, true, dest);

    // Draw text
    g_graphicsModule.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    dest.h /= CONSOLE_STRING_HEIGHT;

    for (i32f i = 0; i < CONSOLE_STRING_HEIGHT; dest.y += dest.h, ++i)
    {
        i32f tempIndex = (i + 1) * CONSOLE_STRING_WIDTH;
        u8 temp = m_buffer[tempIndex]; // Save start of next string that will be null terminated
        m_buffer[tempIndex] = 0;

        g_graphicsModule.DrawText(RENDER_MODE_DEBUG, 1, true, dest, (const char*) &m_buffer[i * CONSOLE_STRING_WIDTH], GraphicsModule::s_pConsoleFont);

        m_buffer[tempIndex] = temp; // Restore
    }

    // Draw cursor
    s32 letterWidth = g_graphicsModule.GetScreenWidth() / CONSOLE_STRING_WIDTH;
    s32 letterHeight = (g_graphicsModule.GetScreenHeight() / 2) / CONSOLE_STRING_HEIGHT;
    s32 underscoreHeight = letterHeight / 5;

    dest = {
        (m_cursorPosition - CONSOLE_INPUT_INDEX) * letterWidth,
        g_graphicsModule.GetScreenHeight() / 2 - underscoreHeight,
        letterWidth,
        underscoreHeight
    };

    g_graphicsModule.SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    g_graphicsModule.FillRect(RENDER_MODE_DEBUG, 2, true, dest);
}

void Console::Print(const char* text)
{
    for (i32f y = m_currentRow * CONSOLE_STRING_WIDTH, x = 0, j = 0; text[j]; ++x, ++j)
    {
        if (text[j] == '\n')
        {
            LineFeed();
            y = m_currentRow * CONSOLE_STRING_WIDTH;
            x = 0;
            continue;
        }

        if (x >= CONSOLE_STRING_WIDTH)
        {
            LineFeed();
            y = m_currentRow * CONSOLE_STRING_WIDTH;
            x = 0;
        }

        m_buffer[y + x] = text[j];
    }
}

void Console::Input(i32f ch)
{
    // Check if it's special symbol
    switch (ch)
    {
    case SDLK_ESCAPE: Reset(); return;
    case SDLK_RETURN: Interpret(); return;
    case SDLK_BACKSPACE: Erase(); return;

    case SDLK_UP:
    case SDLK_LEFT:
    case SDLK_DOWN:
    case SDLK_RIGHT:
    {
        Arrow(ch);
        return;
    }

    default: break;
    }

    // Return if there no space for new character
    if (m_currentInput >= CONSOLE_BUFSIZE - 1)
        return;

    // Place character
    if (m_cursorPosition >= m_currentInput)
    {
        m_buffer[m_currentInput] = (u8)ch;
        ++m_currentInput;
        ++m_cursorPosition;
    }
    else
    {
        memmove(&m_buffer[m_cursorPosition + 1], &m_buffer[m_cursorPosition], (CONSOLE_BUFSIZE - 1) - (m_cursorPosition + 1));
        m_buffer[m_cursorPosition] = (u8)ch;
        ++m_currentInput;
        ++m_cursorPosition;
    }
}

void Console::Clear()
{
    // Clear buffer
    memset(m_buffer, ' ', CONSOLE_BUFSIZE-1);
    m_buffer[CONSOLE_BUFSIZE - 1] = 0;

    // Reset row
    m_currentRow = 0;
}

void Console::Arrow(i32f ch)
{
    switch (ch)
    {

    case SDLK_UP:
    case SDLK_DOWN:
    {
        s32 tempInt = m_lastCursorPosition;
        m_lastCursorPosition = m_cursorPosition;
        m_cursorPosition = tempInt;

        tempInt = m_lastInputPosition;
        m_lastInputPosition = m_currentInput;
        m_currentInput = tempInt;

        u8 temp[LAST_BUFSIZE];
        memcpy(temp, &m_buffer[CONSOLE_INPUT_INDEX], LAST_BUFSIZE);
        memcpy(&m_buffer[CONSOLE_INPUT_INDEX], m_lastInput, LAST_BUFSIZE);
        memcpy(m_lastInput, temp, LAST_BUFSIZE);
    } break;

    case SDLK_LEFT:
    {
        if (m_cursorPosition > CONSOLE_INPUT_INDEX + strlen(s_consolePrompt))
            --m_cursorPosition;
    } break;

    case SDLK_RIGHT:
    {
        if (m_cursorPosition < m_currentInput)
            ++m_cursorPosition;
    } break;

    default: {} break;

    }
}

void Console::Interpret()
{
    // Save this input
    memcpy(m_lastInput, &m_buffer[CONSOLE_INPUT_INDEX], LAST_BUFSIZE);
    m_lastCursorPosition = m_cursorPosition;
    m_lastInputPosition = m_currentInput;

    // Null-terminate input string
    if (m_currentInput < CONSOLE_BUFSIZE - 1)
        m_buffer[m_currentInput] = 0;

    // Interpret it
    g_scriptModule.Interpret((const char*)&m_buffer[CONSOLE_INPUT_INDEX + strlen(s_consolePrompt)]);

    // Reset console's input
    Reset();
}

void Console::LineFeed()
{
    if (m_currentRow >= CONSOLE_STRING_HEIGHT - 2)
    {
        memcpy(m_buffer, &m_buffer[CONSOLE_STRING_WIDTH],
               CONSOLE_STRING_WIDTH * (CONSOLE_STRING_HEIGHT - 2));
        memset(&m_buffer[CONSOLE_STRING_WIDTH * (CONSOLE_STRING_HEIGHT - 2)], ' ',
               CONSOLE_STRING_WIDTH);
    }
    else
    {
        ++m_currentRow;
    }
}

void Console::Erase()
{
    if (m_cursorPosition > CONSOLE_INPUT_INDEX + strlen(s_consolePrompt))
    {
        memcpy(&m_buffer[m_cursorPosition - 1], &m_buffer[m_cursorPosition], (CONSOLE_BUFSIZE - 1) - m_cursorPosition);
        --m_cursorPosition;
        --m_currentInput;
        m_buffer[m_currentInput] = ' ';
    }
}

void Console::Reset()
{
    m_currentInput = CONSOLE_INPUT_INDEX + (s32)strlen(s_consolePrompt);
    m_cursorPosition = m_currentInput;

    memset(&m_buffer[CONSOLE_INPUT_INDEX], ' ', CONSOLE_STRING_WIDTH);
    memcpy(&m_buffer[CONSOLE_INPUT_INDEX], s_consolePrompt, strlen(s_consolePrompt));
}
