/* TODO
 */

#ifndef ENTITY_H_
#define ENTITY_H_

/* ====== INCLUDES ====== */
#include "GraphicsModule.h"
#include "AnimationModule.h"

/* ====== STRUCTURES ====== */
class Entity
{
protected:
    Vector2 m_vPosition;
    Vector2 m_vVelocity;
    s32 m_width;
    s32 m_height;
    FRect m_hitBox; // Relative to entity position
    b32 m_bCollidable;
    f32 m_angle;

    s32 m_animFrame;
    f32 m_animElapsed;
    const GT_Animation* m_pAnim;
    const GT_Texture* m_pTexture;
public:
    virtual ~Entity() {}

    virtual void Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture);
    virtual void Clean() {}

    virtual void Update(f32 dtTime) {}
    virtual void Draw();

    const Vector2& GetPosition() const { return m_vPosition; }
    const Vector2& GetVelocity() const { return m_vVelocity; }
    s32 GetWidth() const { return m_width; }
    s32 GetHeight() const { return m_height; }
    const FRect& GetHitBox() const { return m_hitBox; }
    b32 IsCollidable() const { return m_bCollidable; }
    f32 GetAngle() const { return m_angle; }

    void SetPosition(const Vector2& vPosition) { m_vPosition = vPosition; }
    void SetVelocity(const Vector2& vVelocity) { m_vVelocity = vVelocity; }
    void SetPosition(f32 x, f32 y) { m_vPosition.x = x; m_vPosition.y = y; }
    void SetVelocity(f32 x, f32 y) { m_vVelocity.x = x; m_vVelocity.y = y; }

    void SetWidth(s32 width) { m_width = width; }
    void SetHeight(s32 height) { m_height = height; }
    void SetCollidable(b32 bCollidable) { m_bCollidable = bCollidable; }
    void SetAngle(f32 angle) { m_angle = angle; }

    void SetTexture(const GT_Texture* pTexture) { m_pTexture = pTexture; }
};

/* ====== METHODS ====== */
inline void Entity::Draw() {
    // m_width >> 1 == m_width/2
    SDL_Rect dstRect = { (s32)m_vPosition.x - (m_width >> 1),
                         (s32)m_vPosition.y - (m_height >> 1),
                         m_width, m_height };
    if (m_pAnim)
        g_graphicsModule.Draw(m_pTexture, m_pAnim->row, m_animFrame, &dstRect, m_angle, m_pAnim->flip);
    else
        g_graphicsModule.Draw(m_pTexture, 0, 0, &dstRect, m_angle);
}

#endif // ENTITY_H_