/* TODO
 * - Make GT2D engine it's module? just for AddNote()
 * - Log errors
 */

/* ====== INCLUDES ====== */
#include "SDL.h"
#include "SDL_mixer.h"

#include "DebugLogManager.h"
#include "ClockManager.h"
#include "GTMath.h"
#include "InputModule.h"
#include "SoundModule.h"
#include "Game.h"

#include "GT2D.h"

/* ====== DEFINES ====== */
#define FPS 60

/* ====== VARIABLES ====== */
GT2D g_GT2D;

/* ====== METHODS ====== */
b32 GT2D::StartUp()
{
    // Start up log manager
    if (!g_debugLogMgr.StartUp())
        return false;

    { // Init all SDL stuff
        if (0 != SDL_Init(SDL_INIT_EVERYTHING))
        {
            // SDL_GetError()
            return false;
        }

        // Create window and renderer
        if (0 != SDL_CreateWindowAndRenderer(1280, 720,
                                             SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS,
                                             &m_pWindow, &m_pRenderer))
        {
            return false;
        }

        // Init SDL Mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            // Mix_GetError()
            return false;
        }
    }

    { // Start up engine`s modules
        if (!g_clockMgr.StartUp(FPS))
            return false;
        if (!GTM::StartUp())
            return false;
        if (!g_inputModule.StartUp())
            return false;
        if (!g_soundModule.StartUp())
            return false;
        if (!g_game.StartUp())
            return false;
    }

    // Success
    return true;
}

void GT2D::ShutDown()
{
    { // Shut down SDL
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);

        Mix_Quit();
        SDL_Quit();
    }

    { // Shut down engine's modules
        g_game.ShutDown();
        g_soundModule.ShutDown();
        g_inputModule.ShutDown();
        GTM::ShutDown();
        g_clockMgr.ShutDown();
    }

    // Shut down log manager
    g_debugLogMgr.ShutDown();
}

s32 GT2D::Run()
{
    while (g_game.Running())
    {
        if (!g_inputModule.HandleEvents())
            break;

        g_game.Update(g_clockMgr.GetDelta());
        g_game.Render();

        g_clockMgr.Sync();
    }

    return EC_OK;
}