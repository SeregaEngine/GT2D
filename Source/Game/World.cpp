/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "DamageManager.h"

#include "World.h"

/* ====== DEFINES ====== */
#define CAMERA_DEFAULT_X 0
#define CAMERA_DEFAULT_Y 0
#define CAMERA_BOUNDS_DEFAULT_X1 0
#define CAMERA_BOUNDS_DEFAULT_Y1 0
#define CAMERA_BOUNDS_DEFAULT_X2 ( g_graphicsModule.GetScreenWidth() - 1 )
#define CAMERA_BOUNDS_DEFAULT_Y2 ( g_graphicsModule.GetScreenHeight() - 1 )

/* ====== METHODS ====== */
void World::StartUp()
{
    // Set default camera
    g_graphicsModule.GetCamera().SetBounds({ CAMERA_BOUNDS_DEFAULT_X1, CAMERA_BOUNDS_DEFAULT_Y1,
                                             CAMERA_BOUNDS_DEFAULT_X2, CAMERA_BOUNDS_DEFAULT_Y2 });
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
    m_lstRemove.Clean();
    m_lstEvent.Clean();

    AddNote(PR_NOTE, "World shut down");
}

void World::Update(f32 dtTime)
{
    UpdateEntities(dtTime);
    HandleEvents();
    RemoveEntities();
}

void World::Render()
{
    // Draw parallax
    SDL_Rect rect = { 0, 0, g_graphicsModule.GetScreenWidth() * 2,
                            g_graphicsModule.GetScreenHeight() };
    g_graphicsModule.Draw(m_pParallax, 0, 0, &rect);

    // Draw background
    rect = { 0, 0, g_graphicsModule.GetScreenWidth(), g_graphicsModule.GetScreenHeight() };
    g_graphicsModule.Draw(m_pBackground, 0, 0, &rect);
    rect.x = rect.w;
    g_graphicsModule.Draw(m_pBackground, 0, 1, &rect);

    // Draw entities
    m_lstEntity.Mapcar([](auto pEntity) {
        pEntity->Draw();
    });
}

void World::UpdateEntities(f32 dtTime)
{
    auto end = m_lstEntity.End();
    for (auto it = m_lstEntity.Begin(); it != end; ++it)
        it->data->Update(dtTime);
}

void World::HandleEvents()
{
    // Handle events
    auto end = m_lstEvent.End();
    for (auto it = m_lstEvent.Begin(); it != end; ++it)
    {
        switch (it->data.type)
        {
        case WORLD_EVENT_ATTACK:
        {
            g_damageMgr.HandleAttack(it->data.attack);
            // TODO(sean) Play weapon's sound
        } break;

        default: {} break;
        }
    }

    // Free memory
    m_lstEvent.Clean();
}

void World::RemoveEntities()
{
    auto end = m_lstRemove.End();
    for (auto it = m_lstRemove.Begin(); it != end; ++it)
    {
        // Remove from entity list
        m_lstEntity.Remove(it->data);

        // Free memory
        it->data->Clean();
        delete it->data;
    }

    // Clean remove list
    m_lstRemove.Clean();
}
