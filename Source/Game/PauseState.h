#pragma once

#include "ScriptModule.h"
#include "World.h"
#include "GameState.h"

class PauseState : public GameState
{
    lua_State* m_pPrevious;
    World& m_world;

public:
    PauseState(lua_State* pPrevious, World& world) :
        GameState(GAME_STATE_PAUSE), m_pPrevious(pPrevious), m_world(world) {}

    virtual b32 OnEnter() override;
    virtual void OnExit() override;

    virtual void Update(f32 dtTime) override { g_scriptModule.UpdateMission(m_pScript, dtTime); }
    virtual void Render() override;

    World& GetWorld() { return m_world; }
};
