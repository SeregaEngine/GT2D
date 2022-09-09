/* ====== INCLUDES ====== */
#include "Player.h"

#include "PlayState.h"

/* ====== METHODS ====== */
b32 PlayState::OnEnter()
{
    // Background
    m_pBackground = g_graphicsModule.LoadTexture(TID_MISSION1, TFN_MISSION1, TW_LOCATION, TH_LOCATION);
    m_pParallax = g_graphicsModule.LoadTexture(TID_MISSION1_PARALLAX, TFN_MISSION1_PARALLAX, TW_PARALLAX, TH_PARALLAX);

    // Player
    m_pPlayer = new Player();
    m_pPlayer->Init(Vec2(10.0f * g_unitX, 0.0f * g_unitY),
                    (s32)(TW_ACTOR * g_unitX), (s32)(TH_ACTOR * g_unitY),
                    FRect(-8.0f * g_unitX, -8.0f * g_unitY, 8.0f * g_unitX, 8.0f * g_unitY),
                    g_graphicsModule.LoadTexture(TID_PLAYER, TFN_PLAYER, TW_ACTOR, TH_ACTOR));

    // Set camera
    g_graphicsModule.GetCamera().SetBoundary({ 0, 0, (s32)(TW_LOCATION * g_unitX * 2) - 1,
                                                     (s32)(TH_LOCATION * g_unitY) - 1 });
    g_graphicsModule.GetCamera().Attach(m_pPlayer);

    return true;
}

void PlayState::OnExit()
{
    // TODO(sean) unload texture separately with entities
    m_pPlayer->Clean();
    delete m_pPlayer;

    g_graphicsModule.UnloadTexture(m_pBackground);
}

void PlayState::Update(f32 dtTime)
{
    m_pPlayer->Update(dtTime);
}

void PlayState::Render()
{
    // Draw background
    SDL_Rect back = { 0, 0, (s32)(TW_PARALLAX * g_unitX), (s32)(TH_PARALLAX * g_unitY) };
    g_graphicsModule.Draw(m_pParallax, 0, 0, &back);

    back = { 0, 0, (s32)(TW_LOCATION * g_unitX), (s32)(TH_LOCATION * g_unitY) };
    g_graphicsModule.Draw(m_pBackground, 0, 0, &back);
    back.x = back.w;
    g_graphicsModule.Draw(m_pBackground, 0, 1, &back);

    // Draw player
    m_pPlayer->Draw();
}
