#pragma once

#include "Engine/Types.h"
#include "Engine/EngineModule.h"
#include "Game/GameState.h"
#include "Game/PlayState.h"
#include "Game/World.h"

struct lua_State;

class Game final : public EngineModule
{
    b32 m_bRunning;

    GameState* m_pCurrentState;
    TList<GameState*> m_lstState;
    TList<GameState*> m_lstRemove;

public:
    Game() : EngineModule("Game", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime);
    void Render() const;
    forceinline void Stop() { m_bRunning = false; }

    forceinline void PushState(GameState* pState) { m_lstState.Push(pState); }
    forceinline void PopState();
    forceinline void PopAllStates() { m_lstState.Foreach([] (auto pState, auto pSelf) { static_cast<Game*>(pSelf)->m_lstRemove.Push(pState); }, this); }
    forceinline void ChangeState(GameState* pState);
    forceinline GameState* GetCurrentState() const { return m_pCurrentState; }

    forceinline b32 Running() const { return m_bRunning; }
    World& GetWorld();
    forceinline lua_State* GetScript() const { return m_pCurrentState ? m_pCurrentState->GetScript() : nullptr; };

private:
    void HandleNewState();
    void RemoveStates();
};

inline Game g_game;

forceinline void Game::PopState()
{
    if (m_pCurrentState)
    { 
        m_lstRemove.Push(m_pCurrentState);
    }
}

forceinline void Game::ChangeState(GameState* pState)
{
    PopState();
    PushState(pState);
}

