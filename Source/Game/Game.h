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
    void Stop() { m_bRunning = false; }

    void PushState(GameState* pState) { m_lstState.Push(pState); }
    void PopState() { if (m_pCurrentState) m_lstRemove.Push(m_pCurrentState); }
    void PopAllStates() { m_lstState.Foreach([](auto pState, auto pSelf) { static_cast<Game*>(pSelf)->m_lstRemove.Push(pState); }, this); }
    void ChangeState(GameState* pState) { PopState(); PushState(pState); }
    GameState* GetCurrentState() { return m_pCurrentState; }

    b32 Running() const { return m_bRunning; }
    World& GetWorld();
    lua_State* GetScript() { return m_pCurrentState ? m_pCurrentState->GetScript() : nullptr; };

private:
    void HandleNewState();
    void RemoveStates();
};

inline Game g_game;
