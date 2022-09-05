#ifndef GT2D_H_
#define GT2D_H_

/* ====== INCLUDES ====== */
#include "SDL.h"

#include "Types.h"

/* ====== STRUCTURES ====== */
class GT2D
{
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
public:
    b32 StartUp();
    void ShutDown();
    s32 Run();
};

extern GT2D g_GT2D;

#endif // GT2D_H_