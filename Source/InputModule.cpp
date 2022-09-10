/* ====== INCLUDES ====== */
#include "InputModule.h"

/* ====== VARIABLES ====== */
InputModule g_inputModule;

/* ====== METHODS ====== */
b32 InputModule::StartUp()
{
    // Defaults
    m_keyState = SDL_GetKeyboardState(nullptr);
    m_mouseState = 0;
    m_mousePosX = 0;
    m_mousePosY = 0;

    AddNote(PR_NOTE, "Module started");

    return true;
}

void InputModule::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

b32 InputModule::HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {

        case SDL_QUIT:
        {
            AddNote(PR_NOTE, "SDL_QUIT event");
            return false;
        } break;

        default: {} break;

        }
    }

    m_mouseState = SDL_GetMouseState(&m_mousePosX, &m_mousePosY);

    return true;
}