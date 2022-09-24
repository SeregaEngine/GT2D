#ifndef WORLD_H_
#define WORLD_H_

/* ====== INCLUDES ====== */
#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"
#include "WorldEvent.h"

/* ====== STRUCTURES ====== */
class Weapon;

class World final : EngineModule
{
    GT_Texture* m_pBackground;
    GT_Texture* m_pParallax;
    SRect m_groundBounds;

    TList<Entity*> m_lstEntity;
    TList<Entity*> m_lstRemove;
    TList<Weapon*> m_lstWeapon;
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
    void PushWeapon(Weapon* pWeapon) { m_lstWeapon.Push(pWeapon); }
    void PushEvent(WorldEvent& event) { m_lstEvent.Push(event); }
private:
    void UpdateEntities(f32 dtTime);
    void HandleEvents();
    void RemoveEntities();
};

#endif // WORLD_H_
