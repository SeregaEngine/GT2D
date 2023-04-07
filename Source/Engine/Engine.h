#pragma once

#include "SDL.h"
#include "Engine/EngineModule.h"

class Engine final : public EngineModule
{
public:
    enum eExitCode
    {
        EC_OK = 0,
        EC_ERROR = 1
    };

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

public:
    Engine() :
        EngineModule("GT2D", CHANNEL_GT2D),
        m_pWindow(nullptr), m_pRenderer(nullptr) {}
    ~Engine() {}

    b32 StartUp();
    void ShutDown();
    s32 Run();
};

inline Engine g_engine;