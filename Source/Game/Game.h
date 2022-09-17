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
public:
    Game() : EngineModule("Game", CHANNEL_GAME) {}

    b32 StartUp();
    void ShutDown();

    void Stop() { m_bRunning = false; }

    b32 Running() const { return m_bRunning; }
    GameState* GetCurrentState() { return m_pCurrentState; }
    World& GetWorld() { return static_cast<PlayState*>(m_pCurrentState)->GetWorld(); }

    void Update(f32 dtTime);
    void Render() const;
};

extern Game g_game;

#endif // GAME_H_
