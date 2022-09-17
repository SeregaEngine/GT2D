/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "PlayState.h"
#include "ClockManager.h"

#include "Game.h"

/* ====== VARIABLES ====== */
Game g_game;

/* ====== METHODS====== */
b32 Game::StartUp()
{
    // Defaults
    m_bRunning = true;

    m_pCurrentState = new PlayState();
    m_pCurrentState->OnEnter();

    // Stabilize delta time
    g_clockMgr.GetDelta();

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Game::ShutDown()
{
    if (m_pCurrentState)
    {
        m_pCurrentState->OnExit();
        delete m_pCurrentState;
    }

    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    m_pCurrentState->Update(dtTime);
}

void Game::Render() const
{
    g_graphicsModule.ClearScreen();
    m_pCurrentState->Render();
    g_graphicsModule.FlipScreen();
}
