#ifndef GAMESTATE_H_
#define GAMESTATE_H_

/* ====== INCLUDES ====== */
#include "Types.h"

/* ====== STRUCTURES ====== */
struct lua_State;

class GameState
{
protected:
    lua_State* m_pScript;
public:
    GameState() : m_pScript(nullptr) {}
    virtual ~GameState() {}

    virtual b32 OnEnter() { return true; }
    virtual void OnExit() {}

    virtual void Update(f32 dtTime) {}
    virtual void Render() {}

    lua_State* GetScript() { return m_pScript; }
};

#endif // GAMESTATE_H_