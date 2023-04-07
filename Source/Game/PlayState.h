#pragma once

#include "Game/GameState.h"
#include "Game/World.h"

static constexpr i32f PLAYSTATE_PATH_STRSIZE = 32;

class PlayState final : public GameState
{
    char m_scriptPath[PLAYSTATE_PATH_STRSIZE];
    s32 m_loadLocation;

    World m_world;

public:
    PlayState(const char* scriptPath, s32 loadLocation) :
        GameState(GAME_STATE_PLAY), m_scriptPath(), m_loadLocation(loadLocation), m_world()
        { strncpy(m_scriptPath, scriptPath, PLAYSTATE_PATH_STRSIZE); }

    virtual b32 OnEnter() override;
    virtual void OnExit() override;

    virtual void Update(f32 dtTime) override;
    virtual void Render() override;

    World& GetWorld() { return m_world; }
    const char* GetScriptPath() const { return m_scriptPath; }
};
