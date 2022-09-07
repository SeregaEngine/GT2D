/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "InputModule.h"
#include "SoundModule.h"
#include "Entity.h"

#include "Game.h"

/* ====== VARIABLES ====== */
Game g_game;

static GT_Texture* debug;
static Entity debugEntity;

/* ====== METHODS====== */
b32 Game::StartUp()
{
    // Defaults
    m_bRunning = true;

    debug = g_graphicsModule.LoadTexture(0, "Textures/Locations/Garage.png", 128, 72);
    debugEntity.SetTexture(g_graphicsModule.LoadTexture(1, "Textures/Actors/actor.png", 72, 80));
    debugEntity.SetWidth(72);
    debugEntity.SetHeight(80);
    debugEntity.SetPosition({ 500.0f, 200.0f });
    debugEntity.SetVelocity({ 0.0f, 0.0f });

    AddNote(PR_NOTE, "Module started");

    return true;
}

void Game::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

void Game::Update(f32 dtTime)
{
    m_dtTime = dtTime;

    if (g_inputModule.IsKeyDown(SDLK_ESCAPE))
        m_bRunning = false;

    if (g_inputModule.IsKeyDown(SDLK_w))
        debugEntity.SetVelocity({ debugEntity.GetVelocity().x, -5.0f });
    if (g_inputModule.IsKeyDown(SDLK_s))
        debugEntity.SetVelocity({ debugEntity.GetVelocity().x, 5.0f });
    if (g_inputModule.IsKeyDown(SDLK_a))
        debugEntity.SetVelocity({ -5.0f, debugEntity.GetVelocity().y});
    if (g_inputModule.IsKeyDown(SDLK_d))
        debugEntity.SetVelocity({ 5.0f, debugEntity.GetVelocity().y });

    debugEntity.SetPosition({debugEntity.GetPosition().x + debugEntity.GetVelocity().x, debugEntity.GetPosition().y + debugEntity.GetVelocity().y});
}

void Game::Render() const
{
    g_graphicsModule.ClearScreen();

    g_graphicsModule.Draw(debug, 0, 0, nullptr);
    debugEntity.Draw();

    g_graphicsModule.FlipScreen();
}
