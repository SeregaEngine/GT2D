#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Math/GTMath.h"
#include "Graphics/GraphicsModule.h"
#include "Input/InputModule.h"
#include "Sound/SoundModule.h"
#include "Animation/AnimationModule.h"
#include "Script/ScriptModule.h"
#include "Game/DamageManager.h"
#include "Game/Game.h"
#include "Engine/DebugLogManager.h"
#include "Engine/Console.h"
#include "Engine/ClockManager.h"
#include "Engine/CollisionManager.h"
#include "Engine/GT2D.h"

static constexpr i32f DEFAULT_FPS = 60;
static constexpr i32f DEFAULT_SCREEN_WIDTH = 1280;
static constexpr i32f DEFAULT_SCREEN_HEIGHT = 720;

static constexpr char WINDOW_TITLE[] =
#ifdef _DEBUG
    "GT2D";
#else
    "Petrol: The Fastest";
#endif

b32 GT2D::StartUp()
{
    // Start up log manager
    if (!g_debugLogMgr.StartUp())
    {
        return false;
    }

    { // Init all SDL stuff
        if (0 != SDL_Init(SDL_INIT_EVERYTHING))
        {
            AddNote(PR_ERROR, "Error on SDL initialization: %s", SDL_GetError());
            return false;
        }

        // Create window
        Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS;
#ifdef NDEBUG
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

        if ( nullptr == (m_pWindow = SDL_CreateWindow(
                            WINDOW_TITLE,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
                            windowFlags)) )
        {
            AddNote(PR_ERROR, "Error on creating window: %s", SDL_GetError());
            return false;
        }

        // Create renderer
        if ( nullptr == (m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) )
        {
            AddNote(PR_ERROR, "Error on creating renderer: %s", SDL_GetError());
            return false;
        }
        SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

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
        {
            return false;
        }

        s32 width, height;
        SDL_GetWindowSize(m_pWindow, &width, &height);

        if (!g_graphicsModule.StartUp(m_pWindow, m_pRenderer, width, height)) return false;
        if (!g_inputModule.StartUp())  return false;
        if (!g_soundModule.StartUp())  return false;
        if (!g_animModule.StartUp())   return false;
        if (!g_scriptModule.StartUp()) return false;
        if (!g_game.StartUp())         return false;
        if (!g_collisionMgr.StartUp()) return false;
        if (!g_damageMgr.StartUp())    return false;
        if (!g_clockMgr.StartUp(DEFAULT_FPS))  return false;
    }

    AddNote(PR_NOTE, "Engine started successfully\n");

    // Success
    return true;
}

void GT2D::ShutDown()
{
    AddNote(PR_NOTE, "Engine shut down");

    { // Shut down engine's modules
        g_clockMgr.ShutDown();
        g_damageMgr.ShutDown();
        g_collisionMgr.ShutDown();
        g_game.ShutDown();
        g_scriptModule.ShutDown();
        g_animModule.ShutDown();
        g_soundModule.ShutDown();
        g_inputModule.ShutDown();
        g_graphicsModule.ShutDown();
        GTM::ShutDown();
    }

    AddNote(PR_NOTE, "Engine modules shut down");

    { // Shut down SDL
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);

        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    AddNote(PR_NOTE, "SDL modules shut down");

    // Shut down log manager
    g_debugLogMgr.ShutDown();
}

s32 GT2D::Run()
{
    while (g_game.Running())
    {
        if (!g_inputModule.HandleEvents())
        {
            break;
        }

        g_game.Update(g_clockMgr.ComputeDelta());
        g_game.Render();

        // NOTE: Now we use VSync instead of clock synchronization
        // g_clockMgr.Sync();
    }

    return EC_OK;
}
