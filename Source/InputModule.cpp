/* ====== INCLUDES ====== */
#include "InputModule.h"

/* ====== VARIABLES ====== */
InputModule g_inputModule;

/* ====== METHODS ====== */
b32 InputModule::StartUp()
{
    // Set module info
    SetModuleInfo("InputModule", CHANNEL_INPUT);

    // Get snapshot of keyboard state
    m_keyState = SDL_GetKeyboardState(nullptr);

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
            return false;
        } break;

        default: {} break;

        }
    }

    return true;
}