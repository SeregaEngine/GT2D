/* TODO
 * - Make :1 flags from b32
 * - Delete useless functions for public class members
 */

#ifndef ENTITY_H_
#define ENTITY_H_

/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "AnimationModule.h"

/* ====== DEFINES ====== */
enum eEntityType
{
    ENTITY_TYPE_ENTITY = 0,
    ENTITY_TYPE_ACTOR,
    ENTITY_TYPE_CAR,
    ENTITY_TYPE_TRIGGER,
    ENTITY_TYPE_DIALOG,
};

/* ====== STRUCTURES ====== */
class Entity
{
protected:
    s32 m_type;
public:
    Vector2 m_vPosition;
    Vector2 m_vVelocity;

    s32 m_width;
    s32 m_height;

    f32 m_angle;
    SDL_RendererFlip m_flip;

    FRect m_hitBox; // Relative to entity position
    b32 m_bCollidable;

    s32 m_animFrame;
    f32 m_animElapsed;
    const GT_Animation* m_pAnim;

    s32 m_renderMode;
    s32 m_zIndex;
    b32f m_bHUD;
    const GT_Texture* m_pTexture;
public:
    virtual ~Entity() {}

    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    s32 GetType() const { return m_type; }

    void SetPosition(const Vector2& vPosition) { m_vPosition = vPosition; }
    void SetPosition(f32 x, f32 y) { m_vPosition.x = x; m_vPosition.y = y; }
    const Vector2& GetPosition() const { return m_vPosition; }

    void SetVelocity(const Vector2& vVelocity) { m_vVelocity = vVelocity; }
    void SetVelocity(f32 x, f32 y) { m_vVelocity.x = x; m_vVelocity.y = y; }
    const Vector2& GetVelocity() const { return m_vVelocity; }

    void SetWidth(s32 width) { m_width = width; }
    s32 GetWidth() const { return m_width; }
    void SetHeight(s32 height) { m_height = height; }
    s32 GetHeight() const { return m_height; }

    void SetAngle(f32 angle) { m_angle = angle; }
    f32 GetAngle() const { return m_angle; }

    void SetFlip(SDL_RendererFlip flip) { m_flip = flip; }
    SDL_RendererFlip GetFlip() const { return m_flip; }

    void SetHitBox(const FRect& hitBox) { m_hitBox = hitBox; }
    const FRect& GetHitBox() const { return m_hitBox; }

    void ToggleCollidable(b32 bCollidable) { m_bCollidable = bCollidable; }
    b32 IsCollidable() const { return m_bCollidable; }

    void SetAnimFrame(s32 animFrame) { m_animFrame = animFrame; }
    s32 GetAnimFrame() const { return m_animFrame; }

    void SetAnimElapsed(f32 animElapsed) { m_animElapsed = animElapsed; }
    f32 GetAnimElapsed() const { return m_animElapsed; }

    void SetAnim(const GT_Animation* pAnim) { m_pAnim = pAnim; }
    const GT_Animation* GetAnim() { return m_pAnim; }

    void SetTexture(const GT_Texture* pTexture) { m_pTexture = pTexture; }
    const GT_Texture* GetTexture() const { return m_pTexture; }
};

#endif // ENTITY_H_