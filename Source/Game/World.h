#ifndef WORLD_H_
#define WORLD_H_

/* ====== INCLUDES ====== */
#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"

/* ====== DEFINES ====== */
enum eWorldEvent
{
    WORLD_EVENT_ATTACK = 0,
};

/* ====== STRUCTURES ====== */
struct AttackEvent
{
    // TODO(sean) Maybe this event should contain only attacker?
    Vector2 vPosition;
    FRect hitBox;
    s32 team;
    s32 damage;
};

struct WorldEvent
{
    s32 type;
    union
    {
        AttackEvent attack;
    };

    WorldEvent() = default;
    WorldEvent(const WorldEvent& event) { memcpy(this, &event, sizeof(*this)); };
};

class World final : EngineModule
{
    GT_Texture* m_pBackground;
    GT_Texture* m_pParallax;
    SRect m_groundBounds;

    TList<Entity*> m_lstEntity;
    TList<Entity*> m_lstRemove;
    TList<WorldEvent> m_lstEvent;
public:
    World() : EngineModule("World", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime);
    void Render();

    void SetBackground(GT_Texture* pTexture) { m_pBackground = pTexture; }
    void SetParallax(GT_Texture* pTexture) { m_pParallax = pTexture; }
    void SetGroundBounds(SRect& rect) { m_groundBounds = rect; }

    const SRect& GetGroundBounds() const { return m_groundBounds; }
    TList<Entity*>& GetEntityList() { return m_lstEntity; }

    void PushEntity(Entity* pEntity) { m_lstEntity.Push(pEntity); }
    void RemoveEntity(Entity* pEntity) { m_lstRemove.Push(pEntity); }

    void PushEvent(WorldEvent& event) { m_lstEvent.Push(event); }
private:
    void UpdateEntities(f32 dtTime);
    void HandleEvents();
    void RemoveEntities();
};

#endif // WORLD_H_
