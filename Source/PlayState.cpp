#include "Player.h"

#include "PlayState.h"

b32 PlayState::OnEnter()
{
    m_pBackground = g_graphicsModule.LoadTexture(TID_MISSION1, TFN_MISSION1, TW_LOCATION, TH_LOCATION);

    m_player = new Player();
    m_player->Init(Vec2(100.0f, 0.0f), 160, 160, FRect(-80, -80, 80, 80), g_graphicsModule.LoadTexture(TID_PLAYER, TFN_PLAYER, TW_ACTOR, TH_ACTOR));

    return true;
}

void PlayState::OnExit()
{
    // TODO(sean) unload texture separately with entities
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
    SDL_Rect back = { 0, 0, 1280, 720 };
    g_graphicsModule.Draw(m_pBackground, 0, 0, &back);
    back.x += back.w;
    back.w += back.w;
    g_graphicsModule.Draw(m_pBackground, 0, 1, &back);

    // Draw player
    m_player->Draw();
}
