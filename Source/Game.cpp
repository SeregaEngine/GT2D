/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "PlayState.h"

#include "Game.h"

/* ====== VARIABLES ====== */
Game g_game;

/* ====== METHODS====== */
b32 Game::StartUp()
{
    // Defaults
    m_bRunning = true;

    m_curState = new PlayState();
    m_curState->OnEnter();

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Game::ShutDown()
{
    m_curState->OnExit();
    delete m_curState;

    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    m_curState->Update(dtTime);
}

void Game::Render() const
{
    g_graphicsModule.ClearScreen();
    m_curState->Render();
    g_graphicsModule.FlipScreen();
}
