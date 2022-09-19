/* TODO
 * - Make GT2D engine it's module? just for AddNote()
 * - Log errors
 */

/* ====== INCLUDES ====== */
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "DebugLogManager.h"
#include "ClockManager.h"
#include "GTMath.h"
#include "GraphicsModule.h"
#include "InputModule.h"
#include "SoundModule.h"
#include "AnimationModule.h"
#include "AIModule.h"
#include "ScriptModule.h"
#include "Game.h"
#include "CollisionManager.h"

#include "GT2D.h"

/* ====== DEFINES ====== */
#define FPS 60
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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
            AddNote(PR_ERROR, "Error on SDL initialization: %s", SDL_GetError());
            return false;
        }

        // Create window
        if ( nullptr == (m_pWindow = SDL_CreateWindow(
                            "GT2D",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS)) )
        {
            AddNote(PR_ERROR, "Error on creating window: %s", SDL_GetError());
            return false;
        }

        // Create renderer
        if ( nullptr == (m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED)) )
        {
            AddNote(PR_ERROR, "Error on creating renderer: %s", SDL_GetError());
            return false;
        }

        // Init SDL Image
        if (~IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
        {
            AddNote(PR_ERROR, "Error on SDL Image initialization: %s", IMG_GetError());
            return false;
        }

        // Init SDL Mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            AddNote(PR_ERROR, "Error on SDL Mixer initialization: %s", Mix_GetError());
            return false;
        }

        if (0 != TTF_Init())
        {
            AddNote(PR_ERROR, "%s", TTF_GetError());
            return false;
        }
    }

    { // Start up engine`s modules
        if (!GTM::StartUp())
            return false;
        if (!g_graphicsModule.StartUp(m_pRenderer, SCREEN_WIDTH, SCREEN_HEIGHT))
            return false;
        if (!g_inputModule.StartUp())
            return false;
        if (!g_soundModule.StartUp())
            return false;
        if (!g_animModule.StartUp())
            return false;
        if (!g_AIModule.StartUp())
            return false;
        if (!g_scriptModule.StartUp())
            return false;
        if (!g_game.StartUp())
            return false;
        if (!g_collisionMgr.StartUp())
            return false;
        if (!g_clockMgr.StartUp(FPS))
            return false;
    }

    AddNote(PR_NOTE, "Engine started successfully\n");

    // Success
    return true;
}

void GT2D::ShutDown()
{
    { // Shut down engine's modules
        g_clockMgr.ShutDown();
        g_collisionMgr.ShutDown();
        g_game.ShutDown();
        g_scriptModule.ShutDown();
        g_AIModule.ShutDown();
        g_animModule.ShutDown();
        g_soundModule.ShutDown();
        g_inputModule.ShutDown();
        g_graphicsModule.ShutDown();
        GTM::ShutDown();
    }

    { // Shut down SDL
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);

        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }


    AddNote(PR_NOTE, "Engine shut down");

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