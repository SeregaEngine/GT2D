/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "InputModule.h"
#include "SoundModule.h"

#include "Game.h"

/* ====== VARIABLES ====== */
Game g_game;

static GT_Texture* debug;

/* ====== METHODS====== */
b32 Game::StartUp()
{
    // Defaults
    m_bRunning = true;

    debug = g_graphicsModule.LoadTexture(0, "Locations/Garage.png", 128, 72);

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Game::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    m_dtTime = dtTime;

    if (g_inputModule.IsKeyDown(SDLK_ESCAPE))
        m_bRunning = false;
}

void Game::Render() const
{
    g_graphicsModule.ClearScreen();

    g_graphicsModule.Draw(debug, 0, 0, nullptr);

    g_graphicsModule.FlipScreen();
}
