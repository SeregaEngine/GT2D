/* ====== INCLUDES ====== */
#include "Console.h"

/* ====== DEFINES ====== */
#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 14
#define CONSOLE_BUFSIZE (CONSOLE_WIDTH * CONSOLE_HEIGHT)

/* ====== VARIABLES ====== */
Console g_console;

/* ====== METHODS ====== */
b32f Console::StartUp()
{
    // Allocate and init buffer
    m_buffer = new u8[CONSOLE_BUFSIZE];
    memset(m_buffer, ' ', CONSOLE_BUFSIZE);

    // Don't show by default
    m_bShown = false;

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Console::ShutDown()
{
    delete[] m_buffer;
}
