#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

#include "GraphicsModule.h"
#include "GameState.h"
#include "Entity.h"

class PlayState final: public GameState
{
    GT_Texture* m_pBackground;
    GT_Texture* m_pParallax;
    Entity* m_pPlayer;
public:
    PlayState() : GameState() {}
    virtual ~PlayState() {}

    virtual b32 OnEnter() override;
    virtual void OnExit() override;

    virtual void Update(f32 dtTime) override;
    virtual void Render() override;
};

#endif // PLAYSTATE_H_