/* TODO
 * - Do we really need Player class?
 */

/* ====== INCLUDES ====== */
#include "Game.h"

#include "Player.h"

/* ====== DEFINES ====== */

/* ====== METHODS ====== */
void Player::Init(const Vec2& vPosition, s32 width, s32 height, GT_Texture* pTexture)
{
    Actor::Init(vPosition, width, height, pTexture);

    m_bControllable = true;
}

void Player::Update(f32 dtTime)
{
    // Actor events
    HandleEvents(dtTime);

    // Change position
    m_vPosition = GTM::AddVec2(&m_vPosition, &m_vVelocity);

    if (m_vPosition.x + m_hitBox.x1 < 0.0f)
        m_vPosition.x = 0.0f + m_hitBox.x2;
    else if (m_vPosition.x + m_hitBox.x2 >= TW_LOCATION * g_unitX * 2)
        m_vPosition.x = TW_LOCATION * g_unitX * 2 + m_hitBox.x1;

    f32 legsY = m_vPosition.y + m_hitBox.y2;
    if (legsY < (TH_LOCATION - 16) * g_unitY)
        m_vPosition.y = (TH_LOCATION - 16) * g_unitY + m_hitBox.y1;
    else if (legsY >= TH_LOCATION * g_unitY)
        m_vPosition.y = TH_LOCATION * g_unitY + m_hitBox.y1;

    // Actor animation
    HandleAnimation(dtTime);
}

