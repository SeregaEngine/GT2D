/* ====== INCLUDES ====== */
#include "Game.h"
#include "InputModule.h"

#include "Actor.h"

/* ====== DEFINES ====== */
#define ACTOR_SPEED_X 0.05f
#define ACTOR_SPEED_Y 0.02f

enum eAnimation
{
    ANIM_IDLE_RIGHT = 0,
    ANIM_IDLE_LEFT,
    ANIM_RIGHT,
    ANIM_LEFT,
    ANIM_TOP,
    ANIM_BOTTOM
};

/* ====== VARIABLES ====== */
static const GT_Animation s_aAnims[] =
{
    { 0, 2, 1000.0f / 1.0f, SDL_FLIP_NONE },
    { 0, 2, 1000.0f / 1.0f, SDL_FLIP_HORIZONTAL },
    { 1, 5, 1000.0f / 15.0f, SDL_FLIP_NONE },
    { 1, 5, 1000.0f / 15.0f, SDL_FLIP_HORIZONTAL },
    { 2, 3, 1000.0f / 5.0f, SDL_FLIP_NONE },
    { 3, 3, 1000.0f / 5.0f, SDL_FLIP_NONE }
};

/* ====== METHODS ====== */
void Actor::Init(const Vec2& vPosition, s32 width, s32 height, GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);

    m_state = nullptr;
    m_cmdCounter = 0;
}

void Actor::HandleCommand()
{

}

void Actor::HandleInput(f32 dtTime)
{
    SetVelocity(0.0f, 0.0f);

    if (g_inputModule.IsKeyDown(SDLK_ESCAPE))
    {
        g_game.Stop();
    }

    if (g_inputModule.IsKeyDown(SDLK_w))
    {
        m_vVelocity.y -= ACTOR_SPEED_Y * g_unitY * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_s))
    {
        m_vVelocity.y += ACTOR_SPEED_Y * g_unitY * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_a))
    {
        m_vVelocity.x -= ACTOR_SPEED_X * g_unitX * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_d))
    {
        m_vVelocity.x += ACTOR_SPEED_X * g_unitX * dtTime;
    }
}

void Actor::HandleEvents(f32 dtTime)
{
    if (m_bControllable)
        HandleInput(dtTime);
    else
        HandleCommand();
}

void Actor::HandleAnimation(f32 dtTime)
{
    // Set default animation if we don't have
    if (!m_pAnim)
    {
        m_pAnim = &s_aAnims[ANIM_IDLE_RIGHT];
        m_animFrame = 0;
        m_animElapsed = 0.0f;
        return;
    }

    // Set animation according to actor velocity
    if (m_vVelocity.x > 0)
    {
        m_pAnim = &s_aAnims[ANIM_RIGHT];
    }
    else if (m_vVelocity.x < 0)
    {
        m_pAnim = &s_aAnims[ANIM_LEFT];
    }
    else if (m_vVelocity.y > 0)
    {
        m_pAnim = &s_aAnims[ANIM_BOTTOM];
    }
    else if (m_vVelocity.y < 0)
    {
        m_pAnim = &s_aAnims[ANIM_TOP];
    }
    else
    {
        if (m_pAnim == &s_aAnims[ANIM_LEFT])
            m_pAnim = &s_aAnims[ANIM_IDLE_LEFT];
        else if (m_pAnim != &s_aAnims[ANIM_IDLE_LEFT])
            m_pAnim = &s_aAnims[ANIM_IDLE_RIGHT];
    }

    // Update timer
    m_animElapsed += dtTime;

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
