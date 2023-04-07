#include "Graphics/GraphicsModule.h"
#include "Script/ScriptModule.h"
#include "Game/PlayState.h"
#include "Game/PauseState.h"
#include "Game/Game.h"

void Game::StartUp()
{
    m_bRunning = true;

    m_pCurrentState = nullptr;
    m_lstState.Push(new PlayState(MAIN_MENU_PATH, 0));

    AddNote(PR_NOTE, "Module started");
}

void Game::ShutDown()
{
    m_pCurrentState = nullptr;
    m_lstState.Foreach([](auto pState)
    {
        pState->OnExit();
        delete pState;
    });
    m_lstState.Clean();
    m_lstRemove.Clean();

    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    RemoveStates();
    HandleNewState();
    if (m_pCurrentState)
    {
        m_pCurrentState->Update(dtTime);
    }
}

void Game::Render() const
{
    g_graphicsModule.PrepareToRender();
    if (m_pCurrentState)
    {
        m_pCurrentState->Render();
    }
    g_graphicsModule.Render();
}

void Game::HandleNewState()
{
    if (m_lstState.IsEmpty())
    {
        m_pCurrentState = nullptr;
    }
    else
    {
        if (m_lstState.Front() != m_pCurrentState)
        {
            SDL_ShowCursor(SDL_DISABLE);
            m_pCurrentState = m_lstState.Front();
            if (m_pCurrentState && !m_pCurrentState->IsEntered() && !m_pCurrentState->OnEnter())
            {
                AddNote(PR_ERROR, "False returned on current state's <OnEnter()>");
                PopState();
                m_pCurrentState = nullptr;
                m_bRunning = false;
            }
        }
    }
}

void Game::RemoveStates()
{
    for (auto it = m_lstRemove.Begin(); it; ++it)
    {
        m_lstState.Remove(it->data);
        it->data->OnExit();
        delete it->data;
    }

    m_lstRemove.Clean();
}

World& Game::GetWorld()
{
    s32 id = m_pCurrentState->GetID();
    if (id == GAME_STATE_PLAY)
    {
        return static_cast<PlayState*>(m_pCurrentState)->GetWorld();
    }
    else
    {
        return static_cast<PauseState*>(m_pCurrentState)->GetWorld();
    }
}
