#include "GraphicsModule.h"

#include "World.h"

void World::StartUp()
{
    // Player
    GT_Texture* pTemp = g_graphicsModule.DefineTexture(TFN_PLAYER, TW_ACTOR, TH_ACTOR);
    m_pPlayer = new Player();
    m_pPlayer->Init(Vec2(0.0f * g_unitX, 0.0f * g_unitY),
                    (s32)(TW_ACTOR * g_unitX), (s32)(TH_ACTOR * g_unitY),
                    pTemp);

    m_pPlayer2 = new Player();
    m_pPlayer2->Init(Vec2(20.0f * g_unitX, 65.0f * g_unitY),
                     (s32)(TW_ACTOR * g_unitX), (s32)(TH_ACTOR * g_unitY),
                     pTemp);

    // Set camera
    g_graphicsModule.GetCamera().SetBoundary({ 0, 0, (s32)(TW_LOCATION * g_unitX * 2) - 1,
                                                     (s32)(TH_LOCATION * g_unitY) - 1 });
    g_graphicsModule.GetCamera().Attach(m_pPlayer);

    AddNote(PR_NOTE, "World start up");
}

void World::ShutDown()
{
    m_pPlayer->Clean();
    delete m_pPlayer;
    m_pPlayer2->Clean();
    delete m_pPlayer2;

    AddNote(PR_NOTE, "World shut down");
}

void World::Update(f32 dtTime)
{
    m_pPlayer->Update(dtTime);
    m_pPlayer2->Update(dtTime);
}

void World::Render()
{
    // Draw parallax
    SDL_Rect rect = { 0, 0, (s32)(TW_PARALLAX * g_unitX), (s32)(TH_PARALLAX * g_unitY) };
    g_graphicsModule.Draw(m_pParallax, 0, 0, &rect);

    // Draw background
    rect = { 0, 0, (s32)(TW_LOCATION * g_unitX), (s32)(TH_LOCATION * g_unitY) };
    g_graphicsModule.Draw(m_pBackground, 0, 0, &rect);
    rect.x = rect.w;
    g_graphicsModule.Draw(m_pBackground, 0, 1, &rect);

    // Draw player
    m_pPlayer->Draw();
    m_pPlayer2->Draw();
}