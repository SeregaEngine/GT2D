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

    m_pCurState = new PlayState();
    m_pCurState->OnEnter();

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Game::ShutDown()
{
    if (m_pCurState)
    {
        m_pCurState->OnExit();
        delete m_pCurState;
    }

    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    m_pCurState->Update(dtTime);
}

void Game::Render() const
{
    g_graphicsModule.ClearScreen();
    m_pCurState->Render();
    g_graphicsModule.FlipScreen();
}
