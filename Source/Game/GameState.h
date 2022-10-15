#ifndef GAMESTATE_H_
#define GAMESTATE_H_

/* ====== INCLUDES ====== */
#include "Types.h"

/* ====== DEFINES ====== */
enum eGameStateID
{
    GAME_STATE_PLAY = 0,
    GAME_STATE_PAUSE,
};

/* ====== STRUCTURES ====== */
struct lua_State;

class GameState
{
protected:
    s32 m_id;
    b32 m_bEntered;
    lua_State* m_pScript;
public:
    GameState(s32 id) : m_id(id), m_bEntered(false), m_pScript(nullptr) {}
    virtual ~GameState() {}

    virtual b32 OnEnter() { return true; }
    virtual void OnExit() {}

    virtual void Update(f32 dtTime) {}
    virtual void Render() {}

    s32 GetID() const { return m_id; }
    b32 IsEntered() const { return m_bEntered; }
    lua_State* GetScript() { return m_pScript; }
};

#endif // GAMESTATE_H_