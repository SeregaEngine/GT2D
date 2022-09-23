/* ====== INCLUDES ====== */
#include "Game.h"
#include "InputModule.h"
#include "CollisionManager.h"
#include "GTUnit.h"

#include "Actor.h"

/* ====== DEFINES ====== */
#define ACTOR_UNIT_SPEED_X 0.05f
#define ACTOR_UNIT_SPEED_Y 0.02f

/* ====== VARIABLES ====== */
static const GT_Animation s_aActorAnims[] =
{
    { 0, 2, 1000.0f / 1.0f, SDL_FLIP_NONE },
    { 0, 2, 1000.0f / 1.0f, SDL_FLIP_HORIZONTAL },
    { 1, 5, 1000.0f / 15.0f, SDL_FLIP_NONE },
    { 1, 5, 1000.0f / 15.0f, SDL_FLIP_HORIZONTAL },
    { 2, 3, 1000.0f / 5.0f, SDL_FLIP_NONE },
    { 3, 3, 1000.0f / 5.0f, SDL_FLIP_NONE },

    { 4, 3, 1000.0f / 3.0f, SDL_FLIP_NONE }
};

/* ====== METHODS ====== */
void Actor::Init(const Vector2& vPosition, s32 width, s32 height, GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);

    // Defaults
    m_actorState = ACTOR_STATE_IDLE;

    // Init AI stuff
    m_pState = nullptr;
    m_pTask = nullptr;

    // Init actor animations
    for (i32f i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
        m_aActorAnims[i] = nullptr;

    // Default animations
    { // FIXME(sean) We need static default actor's animations variable
        const GT_Animation* aAnims[MAX_ACTOR_ANIMATIONS];
        for (i32f i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
            aAnims[i] = g_animModule.DefineAnimation(s_aActorAnims[i]);
        SetActorAnims(aAnims);
    }
}

void Actor::Update(f32 dtTime)
{
    HandleState();
    HandleTask();
    HandleCommand(dtTime);
    HandleAnimation(dtTime);
}

void Actor::SetActorAnims(const GT_Animation* aActorAnims[])
{
    // TODO(sean) memcpy()
    for (i32f i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
        m_aActorAnims[i] = aActorAnims[i];
}

void Actor::HandleCommand(f32 dtTime)
{
    // Zero velocity
    m_vVelocity.Zero();

    // Handle command list
    while (!m_lstCommand.IsEmpty())
    {
        GT_Command& cmd = m_lstCommand.Front();
        switch (cmd.cmd)
        {

        case GTC_MOVE_UP:
        case GTC_MOVE_LEFT:
        case GTC_MOVE_DOWN:
        case GTC_MOVE_RIGHT:
        {
            Move(cmd.cmd, dtTime);
        } break;

        case GTC_ATTACK:
        {
            Attack();
        } break;

        default: {} break;

        }
        m_lstCommand.Pop();
    }

    // If we have no velocity
    if (!m_vVelocity.x && !m_vVelocity.y)
    {
        m_actorState = ACTOR_STATE_IDLE;
        return;
    }

    // Compute new position
    Vector2 vNewPosition = m_vPosition + m_vVelocity;
    if (!g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
    {
        // Try move only through x-axis
        vNewPosition.y -= m_vVelocity.y;
        if (!g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
        {
            // Try to move only through y-axis
            vNewPosition.x -= m_vVelocity.x;
            vNewPosition.y += m_vVelocity.y;
            if (!g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
            {
                // TODO(sean) Later we'll may have to set GTT_IMPOSSIBLE status for GotoTask
                // So we'll not move...
                vNewPosition.y -= m_vVelocity.y;
            }
        }
    }

    // Update position
    m_vPosition = vNewPosition;
}

void Actor::Move(s32 cmd, f32 dtTime)
{
    switch (cmd)
    {
    case GTC_MOVE_UP:    m_vVelocity.y -= GTU::UnitToScreenY(ACTOR_UNIT_SPEED_Y) * dtTime; break;
    case GTC_MOVE_LEFT:  m_vVelocity.x -= GTU::UnitToScreenX(ACTOR_UNIT_SPEED_X) * dtTime; break;
    case GTC_MOVE_DOWN:  m_vVelocity.y += GTU::UnitToScreenY(ACTOR_UNIT_SPEED_Y) * dtTime; break;
    case GTC_MOVE_RIGHT: m_vVelocity.x += GTU::UnitToScreenX(ACTOR_UNIT_SPEED_X) * dtTime; break;

    default: break;
    }

    m_actorState = ACTOR_STATE_MOVE;
}

void Actor::Attack()
{
    m_pAnim = m_aActorAnims[ACTOR_ANIMATION_ATTACK];

    m_actorState = ACTOR_STATE_ATTACK;
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

    // If actor is attacking
    if (m_pAnim == m_aActorAnims[ACTOR_ANIMATION_ATTACK])
    {

    }
    else
    {
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
                m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE_LEFT];
            else if (m_pAnim != m_aActorAnims[ACTOR_ANIMATION_IDLE_LEFT])
                m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE_RIGHT];
        }
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
