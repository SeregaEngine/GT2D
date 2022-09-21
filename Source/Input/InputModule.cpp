/* ====== INCLUDES ====== */
#include "Console.h"

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

        case SDL_KEYDOWN:
        {
            OnKeyDown(e);
        } break;

        default: {} break;

        }
    }

    m_mouseState = SDL_GetMouseState(&m_mousePosX, &m_mousePosY);

    return true;
}

void InputModule::OnKeyDown(SDL_Event& e)
{
    // Don't check lshift
    if (e.key.keysym.sym == SDLK_LSHIFT)
        return;

    // Toggle console
    if (e.key.keysym.sym == SDLK_BACKQUOTE)
    {
        g_console.Toggle(~g_console.IsShown());
    }
    // Send input to the console only if it's not backquote and it's shown
    else if (g_console.IsShown())
    {
        // With left shift
        if (IsKeyDown(SDLK_LSHIFT))
        {
            // Uppercase
            if (e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z')
            {
                g_console.Input(e.key.keysym.sym + ('A' - 'a'));
                return;
            }

            // Special symbols
            switch (e.key.keysym.sym)
            {
            case '8': g_console.Input('*'); break;
            case '9': g_console.Input('('); break;
            case '0': g_console.Input(')'); break;
            case '-': g_console.Input('_'); break;
            case '=': g_console.Input('+'); break;
            }
        }
        else // Without left shift
        {
            g_console.Input(e.key.keysym.sym);
        }
    }
}