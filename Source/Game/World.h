#ifndef WORLD_H_
#define WORLD_H_

/* ====== INCLUDES ====== */
#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"
#include "WorldEvent.h"

/* ====== DEFINE ====== */
#define WORLD_SWITCH_STRSIZE 32

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

    char m_switchLocation[WORLD_SWITCH_STRSIZE];
public:
    World() : EngineModule("World", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime);
    void Render();

    void SwitchLocation(const char* funName) { memcpy(m_switchLocation, funName, WORLD_SWITCH_STRSIZE); }

    void SetBackground(GT_Texture* pTexture) { m_pBackground = pTexture; }
    void SetParallax(GT_Texture* pTexture) { m_pParallax = pTexture; }
    void SetGroundBounds(SRect& rect) { m_groundBounds = rect; }

    void PushEntity(Entity* pEntity) { if (pEntity) m_lstEntity.Push(pEntity); }
    void RemoveEntity(Entity* pEntity) { if (pEntity) m_lstRemove.Push(pEntity); }
    void PushWeapon(Weapon* pWeapon) { if (pWeapon) m_lstWeapon.Push(pWeapon); }
    void PushEvent(WorldEvent& event) { m_lstEvent.Push(event); }

    const SRect& GetGroundBounds() const { return m_groundBounds; }
    TList<Entity*>& GetEntityList() { return m_lstEntity; }

    b32f HasEntity(Entity* pEntity) { return m_lstEntity.IsMember(pEntity); }
private:
    void HandleSwitchLocation();
    void UpdateEntities(f32 dtTime);
    void HandleEvents();
    void RemoveEntities();

    void CleanEntities();
    void CleanWeapons();
    void CleanEvents();
};

#endif // WORLD_H_
