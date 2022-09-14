#ifndef WORLD_H_
#define WORLD_H_

#include "EngineModule.h"
#include "Entity.h"
#include "TList.h"

class World final : EngineModule
{
    GT_Texture* m_pBackground;
    GT_Texture* m_pParallax;
    TList<Entity*> m_lstEntity;
public:
    World() : EngineModule("World", CHANNEL_GAME) {}

    void StartUp();
    void ShutDown();

    void Update(f32 dtTime) {}
    void Render();

    void SetBackground(GT_Texture* pTexture) { m_pBackground = pTexture; }
    void SetParallax(GT_Texture* pTexture) { m_pParallax = pTexture; }

    void AddEntity(Entity* pEntity) { m_lstEntity.Push(pEntity); }
};

#endif WORLD_H_
