#include "PlayState.h"

b32 PlayState::OnEnter()
{
    m_pBackground = g_graphicsModule.LoadTexture(TID_MISSION1, "Textures/Locations/Mission1.png", TW_LOCATION, TH_LOCATION);
    m_player.SetWidth(160);
    m_player.SetHeight(160);
    m_player.SetPosition(100.0f, 200.0f);
    m_player.SetTexture(g_graphicsModule.LoadTexture(TID_PLAYER, "Textures/Actors/Player.png", 160, 160));

    return true;
}

void PlayState::OnExit()
{
    g_graphicsModule.UnloadTexture(m_pBackground);
}

void PlayState::Update(f32 dtTime)
{}

void PlayState::Render()
{
    // Draw background
    g_graphicsModule.Draw(m_pBackground, 0, 0, nullptr);
    // Draw player
    m_player.Draw();
}