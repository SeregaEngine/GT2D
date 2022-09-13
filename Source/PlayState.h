#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_

/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "GameState.h"
#include "Entity.h"

/* ====== STRUCTURES ====== */
class PlayState final : public GameState
{
    GT_Texture* m_pBackground;
    GT_Texture* m_pParallax;
    Entity* m_pPlayer;
    Entity* m_pPlayer2;
public:
    virtual b32 OnEnter() override;
    virtual void OnExit() override;

    virtual void Update(f32 dtTime) override;
    virtual void Render() override;

    void SetBackground(GT_Texture* pTexture) { m_pBackground = pTexture; }
    void SetParallax(GT_Texture* pTexture) { m_pParallax = pTexture; }
};

#endif // PLAYSTATE_H_