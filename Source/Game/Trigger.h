#ifndef TRIGGER_H_
#define TRIGGER_H_

/* ====== INCLUDES ====== */
#include <string.h>

#include "Entity.h"

/* ====== DEFINES ====== */
#define TRIGGER_STRSIZE 32

/* ====== STRUCTURES ====== */
class Trigger final : public Entity
{
    char m_functionName[TRIGGER_STRSIZE];
    Entity* m_pAttached;
public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;
    virtual void Draw() override {} // No drawing

    void SetFunctionName(const char* functionName) { strncpy(m_functionName, functionName, TRIGGER_STRSIZE); }
    void AttachEntity(Entity* pEntity) { m_pAttached = pEntity; }
};

#endif // TRIGGER_H_
