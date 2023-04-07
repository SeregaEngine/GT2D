#pragma once

#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"

class Weapon;

class World final : EngineModule
{
    TList<Entity*> m_lstEntity;
    TList<Entity*> m_lstRemove;
    TList<Weapon*> m_lstWeapon;

    SRect m_groundBounds;
    s32 m_switchLocation;

public:
    World() : EngineModule("World", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime);
    void Render();

    void SwitchLocation(s32 location) { m_switchLocation = location; }
    void SetGroundBounds(SRect& rect) { m_groundBounds = rect; }

    void PushEntity(Entity* pEntity);
    void RemoveEntity(Entity* pEntity);
    void PushWeapon(Weapon* pWeapon);

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

inline void World::PushEntity(Entity* pEntity)
{
    if (pEntity)
    {
        m_lstEntity.Push(pEntity);
    }
}

inline void World::RemoveEntity(Entity* pEntity)
{
    if (pEntity)
    {
        m_lstRemove.Push(pEntity);
    }
}

inline void World::PushWeapon(Weapon* pWeapon)
{
    if (pWeapon)
    {
        m_lstWeapon.Push(pWeapon);
    }
}

