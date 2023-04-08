#pragma once

#include "Engine/Types.h"

enum eGameStateID
{
    GAME_STATE_PLAY = 0,
    GAME_STATE_PAUSE,
};

struct lua_State;

class GameState
{
protected:
    s32 m_id;
    b32 m_bEntered;
    lua_State* m_pScript;

public:
    GameState(s32 id) : m_id(id), m_bEntered(false), m_pScript(nullptr) {}
    virtual ~GameState() = default;

    virtual b32 OnEnter() { return true; }
    virtual void OnExit() {}

    virtual void Update(f32 dtTime) {}
    virtual void Render() {}

    forceinline s32 GetID() const { return m_id; }
    forceinline b32 IsEntered() const { return m_bEntered; }
    forceinline lua_State* GetScript() const { return m_pScript; }
};
