#include "Player.h"

#include "PlayState.h"

b32 PlayState::OnEnter()
{
    m_pBackground = g_graphicsModule.LoadTexture(TID_GARAGE, TFN_GARAGE, TW_LOCATION, TH_LOCATION);

    m_player = new Player();
    m_player->Init(Vec2(100.0f, 0.0f), 160, 160, HitBox(-80, -80, 80, 80), g_graphicsModule.LoadTexture(TID_PLAYER, TFN_PLAYER, TW_ACTOR, TH_ACTOR));

    return true;
}

void PlayState::OnExit()
{
    m_player->Clean();
    delete m_player;
    g_graphicsModule.UnloadTexture(m_pBackground);
}

void PlayState::Update(f32 dtTime)
{
    m_player->Update(dtTime);
}

void PlayState::Render()
{
    // Draw background
    g_graphicsModule.Draw(m_pBackground, 0, 0, nullptr);
    // Draw player
    m_player->Draw();
}
