#pragma once

#include "SDL.h"
#include "Engine/EngineModule.h"

class Engine final : public EngineModule
{
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

public:
    Engine() : EngineModule("GT2D", CHANNEL_GT2D) {}
    ~Engine() = default;

    void StartUp();
    void ShutDown();

    /** Returns exit status */
    s32 Run();
};

inline Engine g_engine;
