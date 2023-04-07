#pragma once

#include "Engine/EngineModule.h"
#include "Game/Entity.h"
#include "Containers/List.h"

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
    forceinline void Render() { m_lstEntity.Foreach([] (auto pEntity) { pEntity->Draw(); }); }

    forceinline void SwitchLocation(s32 location) { m_switchLocation = location; }
    forceinline void SetGroundBounds(SRect& rect) { m_groundBounds = rect; }

    void PushEntity(Entity* pEntity);
    void RemoveEntity(Entity* pEntity);
    void PushWeapon(Weapon* pWeapon);

    forceinline const SRect& GetGroundBounds() const { return m_groundBounds; }
    forceinline TList<Entity*>& GetEntityList() { return m_lstEntity; }

    forceinline b32 HasEntity(Entity* pEntity) const { return pEntity ? m_lstEntity.IsMember(pEntity) : false; }

private:
    void HandleSwitchLocation();
    void UpdateEntities(f32 dtTime);
    void RemoveEntities();

    void CleanEntities();
    void CleanWeapons();
};

forceinline  void World::PushEntity(Entity* pEntity)
{
    if (pEntity)
    {
        m_lstEntity.Push(pEntity);
    }
}

forceinline  void World::RemoveEntity(Entity* pEntity)
{
    if (pEntity)
    {
        m_lstRemove.Push(pEntity);
    }
}

forceinline  void World::PushWeapon(Weapon* pWeapon)
{
    if (pWeapon)
    {
        m_lstWeapon.Push(pWeapon);
    }
}

