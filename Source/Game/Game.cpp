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

    m_pCurrentState = nullptr;
    m_lstState.Push(new PlayState());

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Game::ShutDown()
{
    m_pCurrentState = nullptr;
    m_lstState.Mapcar([](auto pState) { pState->OnExit(); delete pState; });
    m_lstState.Clean();
    m_lstRemove.Clean();

    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    RemoveStates();
    HandleNewState();
    if (m_pCurrentState)
        m_pCurrentState->Update(dtTime);
}

void Game::Render() const
{
    g_graphicsModule.PrepareToRender();
    if (m_pCurrentState)
        m_pCurrentState->Render();
    g_graphicsModule.Render();
}

void Game::HandleNewState()
{
    if (m_lstState.Front() != m_pCurrentState)
    {
        m_pCurrentState = m_lstState.Front();
        if (m_pCurrentState)
            m_pCurrentState->OnEnter();
    }
}

void Game::RemoveStates()
{
    auto end = m_lstRemove.End();
    for (auto it = m_lstRemove.Begin(); it != end; ++it)
    {
        m_lstState.Remove(it->data);
        it->data->OnExit();
        delete it->data;
    }

    m_lstRemove.Clean();
}
