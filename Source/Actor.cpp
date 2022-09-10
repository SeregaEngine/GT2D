/* ====== INCLUDES ====== */
#include "Game.h"
#include "InputModule.h"

#include "Actor.h"

/* ====== DEFINES ====== */
#define ACTOR_SPEED_X 0.05f
#define ACTOR_SPEED_Y 0.02f

/* ====== VARIABLES ====== */
static const GT_Animation s_aActorAnims[] =
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

    for (s32 i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
        m_aActorAnims[i] = nullptr;

    // DEBUG(sean)
    for (s32 i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
        m_aActorAnims[i] = &s_aActorAnims[i];

    m_bControllable = false;
    m_state = nullptr;
    m_cmdCounter = 0;
}

void Actor::HandleCmd()
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
        HandleCmd();
}

void Actor::HandleAnimation(f32 dtTime)
{
    // Check if default animations aren't initialized
    if (!m_aActorAnims[ACTOR_ANIMATION_IDLE_RIGHT])
        return;

    // Set default animation if we don't have
    if (!m_pAnim)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE_RIGHT];
        m_animFrame = 0;
        m_animElapsed = 0.0f;
        return;
    }

    // Set animation according to actor velocity
    if (m_vVelocity.x > 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_RIGHT];
    }
    else if (m_vVelocity.x < 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_LEFT];
    }
    else if (m_vVelocity.y > 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_BOTTOM];
    }
    else if (m_vVelocity.y < 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_TOP];
    }
    else
    {
        if (m_pAnim == m_aActorAnims[ACTOR_ANIMATION_LEFT])
            m_pAnim = m_aActorAnims[ACTOR_ANIMATION_LEFT];
        else if (m_pAnim != m_aActorAnims[ACTOR_ANIMATION_LEFT])
            m_pAnim = m_aActorAnims[ACTOR_ANIMATION_RIGHT];
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
