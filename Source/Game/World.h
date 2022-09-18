#ifndef WORLD_H_
#define WORLD_H_

#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"

class World final : EngineModule
{
    GT_Texture* m_pBackground;
    GT_Texture* m_pParallax;
    SRect m_groundBounds;
    TList<Entity*> m_lstEntity;
public:
    World() : EngineModule("World", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime) {}
    void Render();

    void SetBackground(GT_Texture* pTexture) { m_pBackground = pTexture; }
    void SetParallax(GT_Texture* pTexture) { m_pParallax = pTexture; }
    void SetGroundBounds(SRect& rect) { m_groundBounds = rect; }

    const SRect& GetGroundBounds() const { return m_groundBounds; }
    const TList<Entity*>& GetEntityList() const { return m_lstEntity; }

    void AddEntity(Entity* pEntity) { m_lstEntity.Push(pEntity); }
    void UpdateAllEntities(f32 dtTime);
};

#endif // WORLD_H_
