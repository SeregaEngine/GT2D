#include "Console.h"
#include "InputModule.h"

b32 InputModule::StartUp()
{
    m_keyState = SDL_GetKeyboardState(nullptr);
    m_bCapslock = false;

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
    // Don't check some symbols
    switch (e.key.keysym.sym)
    {
    case SDLK_CAPSLOCK:
    {
        m_bCapslock = !m_bCapslock;
        return;
    }

    case SDLK_LSHIFT:
    case SDLK_LALT:
    case SDLK_LCTRL:
    case SDLK_TAB: return;

    default: break;
    }

    if (e.key.keysym.sym == SDLK_BACKQUOTE) // Toggle console
    {
        g_console.Toggle(!g_console.IsShown());
    }
    else if (g_console.IsShown()) // Send input to the console only if it's not backquote and it's shown
    {
        // Check shift
        b32 bShift = IsKeyDown(SDLK_LSHIFT);

        // Latin characters
        if (e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z')
        {
            if (m_bCapslock ^ bShift)
            {
                g_console.Input(e.key.keysym.sym + ('A' - 'a'));
            }
            else
            {
                g_console.Input(e.key.keysym.sym);
            }
            return;
        }

        // With left shift
        if (bShift)
        {
            switch (e.key.keysym.sym)
            {
            case '1': g_console.Input('!'); break;
            case '5': g_console.Input('%'); break;
            case '6': g_console.Input('^'); break;
            case '8': g_console.Input('*'); break;
            case '9': g_console.Input('('); break;
            case '0': g_console.Input(')'); break;
            case '-': g_console.Input('_'); break;
            case '=': g_console.Input('+'); break;

            case ';': g_console.Input(':'); break;
            case '\'': g_console.Input('"'); break;
            case ',': g_console.Input('<'); break;
            case '.': g_console.Input('>'); break;
            case '/': g_console.Input('?'); break;

            default: break;
            }

            return;
        }

        // Other
        g_console.Input(e.key.keysym.sym);
    }
}