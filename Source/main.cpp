#include "SDL.h" // SDL main() function

#include "GT2D.h"

int main(int argc, char** argv)
{
    if (!g_GT2D.StartUp())
        return GT2D::EC_ERROR;

    s32 exitCode = g_GT2D.Run();

    g_GT2D.ShutDown();
    return exitCode;
}