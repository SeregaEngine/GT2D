#include "SDL.h"
#include "Engine/Engine.h"

int main(int argc, char** argv)
{
    if (!g_engine.StartUp())
    {
        return Engine::EC_ERROR;
    }

    s32 exitCode = g_engine.Run();

    g_engine.ShutDown();
    return exitCode;
}