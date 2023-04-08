#pragma once

#include "Engine/StdHeaders.h" 
#include "Game/Entity.h"

class Trigger final : public Entity
{
private:
    static constexpr i32f TRIGGER_STRSIZE = 32;

private:
    char m_functionName[TRIGGER_STRSIZE];

public:
    Entity* m_pAttached;

public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;
    virtual void Draw() override {} /** No drawing */

    forceinline void SetFunctionName(const char* functionName) { std::strncpy(m_functionName, functionName, TRIGGER_STRSIZE); }
    forceinline void Attach(Entity* pEntity) { m_pAttached = pEntity; }
};

