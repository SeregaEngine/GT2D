#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

/* ====== INCLUDES ====== */
#include "GameState.h"
#include "World.h"

/* ====== STRUCTURES ====== */
class PlayState final : public GameState
{
    World m_world;
public:
    virtual b32 OnEnter() override;
    virtual void OnExit() override;

    virtual void Update(f32 dtTime) override;
    virtual void Render() override;

    World& GetWorld() { return m_world; }
};

#endif // PLAYSTATE_H_