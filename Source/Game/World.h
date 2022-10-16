#ifndef WORLD_H_
#define WORLD_H_

/* ====== INCLUDES ====== */
#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"

/* ====== DEFINES ====== */

/* ====== STRUCTURES ====== */
class Weapon;

class World final : EngineModule
{
    TList<Entity*> m_lstEntity;
    TList<Entity*> m_lstRemove;
    TList<Weapon*> m_lstWeapon;

    SRect m_groundBounds;
    s32 m_switchLocation;
    // TODO(sean) World ticks

public:
    World() : EngineModule("World", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime);
    void Render();

    void SwitchLocation(s32 location) { m_switchLocation = location; }
    void SetGroundBounds(SRect& rect) { m_groundBounds = rect; }

    void PushEntity(Entity* pEntity) { if (pEntity) m_lstEntity.Push(pEntity); }
    void RemoveEntity(Entity* pEntity) { if (pEntity) m_lstRemove.Push(pEntity); }
    void PushWeapon(Weapon* pWeapon) { if (pWeapon) m_lstWeapon.Push(pWeapon); }

    const SRect& GetGroundBounds() const { return m_groundBounds; }
    TList<Entity*>& GetEntityList() { return m_lstEntity; }

    b32 HasEntity(Entity* pEntity) { return pEntity ? m_lstEntity.IsMember(pEntity) : false; }
private:
    void HandleSwitchLocation();
    void UpdateEntities(f32 dtTime);
    void RemoveEntities();

    void CleanEntities();
    void CleanWeapons();
};

#endif // WORLD_H_
