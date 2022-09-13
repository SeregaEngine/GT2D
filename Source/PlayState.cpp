/* ====== INCLUDES ====== */
#include "SoundModule.h"
#include "ScriptModule.h"
#include "Player.h"

#include "PlayState.h"

/* ====== METHODS ====== */
b32 PlayState::OnEnter()
{
    // Load mission from lua
    g_scriptModule.LoadMission();

    // Player
    GT_Texture* pTemp = g_graphicsModule.DefineTexture(TID_PLAYER, TFN_PLAYER, TW_ACTOR, TH_ACTOR);
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

    // Sound
    //g_soundModule.PlayMusic(g_soundModule.DefineMusic("Music/TestMusic.mp3"));
    //g_soundModule.PlaySound(g_soundModule.DefineWAV("Sounds/TestSound.wav"));

    return true;
}

void PlayState::OnExit()
{
    m_pPlayer->Clean();
    delete m_pPlayer;
    m_pPlayer2->Clean();
    delete m_pPlayer2;

    g_graphicsModule.UndefineTextures();
    g_animModule.UndefineAnimations();
    g_soundModule.HaltMusic();
    g_soundModule.UndefineResources();

    g_scriptModule.UnloadMission();
}

void PlayState::Update(f32 dtTime)
{
    m_pPlayer->Update(dtTime);
    m_pPlayer2->Update(dtTime);
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
    m_pPlayer2->Draw();
}
