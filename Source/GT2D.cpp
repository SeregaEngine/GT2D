/* ====== INCLUDES ====== */
#include "DebugLogManager.h"
#include "GTMath.h"

#include "GT2D.h"

/* ====== VARIABLES ====== */
GT2D g_GT2D;

/* ====== METHODS ====== */
b32 GT2D::StartUp()
{
    // Start up log manager
    if (!g_debugLogMgr.StartUp())
        return false;

    // Init all SDL subsystems
    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
        return false;

    // Create window and renderer
    SDL_CreateWindowAndRenderer(1280, 720,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS,
                                &m_pWindow, &m_pRenderer);

    // Start up engine`s modules
    if (!GTM::StartUp())
        return false;

    g_debugLogMgr.AddNote(CHANNEL_GT2D, PR_NOTE, "GT2D", "%f", GTM::sinLook[90]);

    SDL_Delay(10000); // DEBUG(sean) remove this

    // Success
    return true;
}

void GT2D::ShutDown()
{
    // Destroy SDL stuff
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);

    // Quit SDL
    SDL_Quit();

    // Shut down engine's modules
    GTM::ShutDown();

    // Shut down log manager
    g_debugLogMgr.ShutDown();
}

s32 GT2D::Run()
{
    return EC_OK;
}