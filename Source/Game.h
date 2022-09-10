#ifndef GAME_H_
#define GAME_H_

/* ====== INCLUDES ====== */
#include "Types.h"
#include "GameState.h"

/* ====== STRUCTURES ====== */
class Game final: public EngineModule
{
    b32 m_bRunning;

    GameState* m_curState;
public:
    Game() :
        EngineModule("Game", CHANNEL_GAME),
        m_bRunning(true), m_curState(nullptr) {}

    b32 StartUp();
    void ShutDown();

    b32 Running() const { return m_bRunning; }
    void Stop() { m_bRunning = false; }

    void Update(f32 dtTime);
    void Render() const;
};

extern Game g_game;

#endif // GAME_H_
