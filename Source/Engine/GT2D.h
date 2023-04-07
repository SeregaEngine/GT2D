#ifndef GT2D_H_
#define GT2D_H_

/* ====== INCLUDES ====== */
#include "SDL.h"

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class GT2D : public EngineModule
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
    GT2D() :
        EngineModule("GT2D", CHANNEL_GT2D),
        m_pWindow(nullptr), m_pRenderer(nullptr) {}
    ~GT2D() {}

    b32 StartUp();
    void ShutDown();
    s32 Run();
};

inline GT2D g_GT2D;

#endif // GT2D_H_