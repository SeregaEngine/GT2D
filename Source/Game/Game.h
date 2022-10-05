#ifndef GAME_H_
#define GAME_H_

/* ====== INCLUDES ====== */
#include "Types.h"
#include "EngineModule.h"
#include "GameState.h"
#include "PlayState.h"
#include "World.h"

/* ====== STRUCTURES ====== */
class Game final : public EngineModule
{
    b32 m_bRunning;

    GameState* m_pCurrentState;
    TList<GameState*> m_lstState;
    TList<GameState*> m_lstRemove;
public:
    Game() : EngineModule("Game", CHANNEL_GAME) {}

    b32 StartUp();
    void ShutDown();

    void Update(f32 dtTime);
    void Render() const;
    void Stop() { m_bRunning = false; }

    void PushState(GameState* pState) { m_lstState.Push(pState); }
    void PopState() { if (m_pCurrentState) m_lstRemove.Push(m_pCurrentState); }
    void ChangeState(GameState* pState) { PopState(); PushState(pState); }
    GameState* GetCurrentState() { return m_pCurrentState; }

    b32 Running() const { return m_bRunning; }
    World& GetWorld() { return static_cast<PlayState*>(m_pCurrentState)->GetWorld(); }
private:
    void HandleNewState();
    void RemoveStates();
};

extern Game g_game;

#endif // GAME_H_
