/* ====== INCLUDES ====== */
#include "GraphicsModule.h"

#include "World.h"

/* ====== DEFINES ====== */
#define CAMERA_DEFAULT_X 0
#define CAMERA_DEFAULT_Y 0

/* ====== METHODS ====== */
void World::StartUp()
{
    // Set camera
    g_graphicsModule.GetCamera().SetBoundary({ 0, 0, (s32)(TW_LOCATION * g_unitX * 2) - 1,
                                                     (s32)(TH_LOCATION * g_unitY) - 1 });
    g_graphicsModule.GetCamera().SetPosition(CAMERA_DEFAULT_X, CAMERA_DEFAULT_Y);

    AddNote(PR_NOTE, "World started");
}

void World::ShutDown()
{
    m_lstEntity.Mapcar([](auto pEntity) {
        pEntity->Clean();
        delete pEntity;
    });
    m_lstEntity.Clean();

    AddNote(PR_NOTE, "World shut down");
}

void World::Update(f32 dtTime)
{
    for (auto it = m_lstEntity.Begin(); it != m_lstEntity.End(); ++it)
        it->data->Update(dtTime);
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
    m_lstEntity.Mapcar([](auto pEntity) {
        pEntity->Draw();
    });
}