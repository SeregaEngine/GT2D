/* TODO
 * - Remember to scale things like speed, boundaries
 */

/* ====== INCLUDES ====== */
#include "InputModule.h"
#include "Game.h"

#include "Player.h"

/* ====== DEFINES ====== */
enum eAnimation
{
    ANIM_IDLE = 0,
    ANIM_RIGHT,
    ANIM_LEFT,
    ANIM_TOP,
    ANIM_BOTTOM
};

static const GT_Animation s_aAnims[] =
{
    { 0, 2, 1000.0f / 1.0f, SDL_FLIP_NONE },
    { 1, 5, 1000.0f / 15.0f, SDL_FLIP_NONE },
    { 1, 5, 1000.0f / 15.0f, SDL_FLIP_HORIZONTAL },
    { 2, 3, 1000.0f / 5.0f, SDL_FLIP_NONE },
    { 3, 3, 1000.0f / 5.0f, SDL_FLIP_NONE }
};

/* ====== METHODS ====== */
void Player::Update(f32 dtTime)
{
    HandleEvents(dtTime);

    m_vPosition = GTM::AddVec2(&m_vPosition, &m_vVelocity);

    if (m_vPosition.x + m_hitBox.x1 < 0.0f)
        m_vPosition.x = 0.0f + m_hitBox.x2;
    else if (m_vPosition.x + m_hitBox.x2 >= 1280.0f*2.0f)
        m_vPosition.x = 1280.0f*2.0f + m_hitBox.x1;

    f32 legsY = m_vPosition.y + m_hitBox.y2;
    if (legsY < 560.0f)
        m_vPosition.y = 560.0f + m_hitBox.y1;
    else if (legsY >= 720.0f)
        m_vPosition.y = 720.0f + m_hitBox.y1;

    HandleAnimation(dtTime);
}

void Player::HandleEvents(f32 dtTime)
{
    SetVelocity(0.0f, 0.0f);

    if (g_inputModule.IsKeyDown(SDLK_ESCAPE))
    {
        g_game.Stop();
    }

    if (g_inputModule.IsKeyDown(SDLK_w))
    {
        m_vVelocity.y -= 0.2f * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_s))
    {
        m_vVelocity.y += 0.2f * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_a))
    {
        m_vVelocity.x -= 0.5f * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_d))
    {
        m_vVelocity.x += 0.5f * dtTime;
    }
}

void Player::HandleAnimation(f32 dtTime)
{
    // Update timer
    m_animElapsed += dtTime;

    // Set default animation if we don't have
    if (!m_pAnim)
    {
        m_pAnim = &s_aAnims[ANIM_IDLE];
        m_animFrame = 0;
        m_animElapsed = 0.0f;
        return;
    }

    // Set animation according to actor velocity
    if (m_vVelocity.x > 0)
        m_pAnim = &s_aAnims[ANIM_RIGHT];
    else if (m_vVelocity.x < 0)
        m_pAnim = &s_aAnims[ANIM_LEFT];
    else if (m_vVelocity.y > 0)
        m_pAnim = &s_aAnims[ANIM_BOTTOM];
    else if (m_vVelocity.y < 0)
        m_pAnim = &s_aAnims[ANIM_TOP];
    else
        m_pAnim = &s_aAnims[ANIM_IDLE];

    // Check if we have to update animation frame
    if (m_animElapsed >= m_pAnim->frameDuration)
    {
        ++m_animFrame;
        m_animElapsed = 0.0f;
    }
    
    // Loop animation
    if (m_animFrame >= m_pAnim->count)
        m_animFrame = 0;
}