#include "SDL.h"
#include "Engine/Engine.h"

int main(int argc, char** argv)
{
    g_engine.StartUp();
    return g_engine.Run();
}
