#include "GT2D.h"

GT2D g_GT2D;

b32 GT2D::StartUp()
{
    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
        return false;

    SDL_CreateWindowAndRenderer(1280, 720,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS,
                                &m_pWindow, &m_pRenderer);

    SDL_Delay(1000);

    return true;
}

void GT2D::ShutDown()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);

    SDL_Quit();
}

s32 GT2D::Run()
{
    return 0;
}