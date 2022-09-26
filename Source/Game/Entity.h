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
    ENTITY_TYPE_TRIGGER,
};

/* ====== STRUCTURES ====== */
class Entity
{
protected:
    s32 m_type;

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

    const GT_Texture* m_pTexture;
public:
    virtual ~Entity() {}

    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    s32 GetType() const { return m_type; }
    const Vector2& GetPosition() const { return m_vPosition; }
    const Vector2& GetVelocity() const { return m_vVelocity; }
    s32 GetWidth() const { return m_width; }
    s32 GetHeight() const { return m_height; }
    f32 GetAngle() const { return m_angle; }
    SDL_RendererFlip GetFlip() const { return m_flip; }
    const FRect& GetHitBox() const { return m_hitBox; }
    b32 IsCollidable() const { return m_bCollidable; }

    void SetPosition(const Vector2& vPosition) { m_vPosition = vPosition; }
    void SetVelocity(const Vector2& vVelocity) { m_vVelocity = vVelocity; }
    void SetPosition(f32 x, f32 y) { m_vPosition.x = x; m_vPosition.y = y; }
    void SetVelocity(f32 x, f32 y) { m_vVelocity.x = x; m_vVelocity.y = y; }

    void SetWidth(s32 width) { m_width = width; }
    void SetHeight(s32 height) { m_height = height; }
    void SetAngle(f32 angle) { m_angle = angle; }
    void SetFlip(SDL_RendererFlip flip) { m_flip = flip; }
    void SetCollidable(b32 bCollidable) { m_bCollidable = bCollidable; }
    void SetTexture(const GT_Texture* pTexture) { m_pTexture = pTexture; }
};

/* ====== METHODS ====== */
inline void Entity::Draw() {
    // m_width >> 1 == m_width/2
    SDL_Rect dstRect = { (s32)m_vPosition.x - (m_width >> 1),
                         (s32)m_vPosition.y - (m_height >> 1),
                         m_width, m_height };

    // TODO(sean) We can have animation by default to remove this branch
    if (m_pAnim)
        g_graphicsModule.Draw(m_pTexture, m_pAnim->row, m_animFrame, &dstRect, m_angle, m_flip);
    else
        g_graphicsModule.Draw(m_pTexture, 0, 0, &dstRect, m_angle, m_flip);
}

#endif // ENTITY_H_