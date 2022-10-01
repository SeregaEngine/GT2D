/* ====== INCLUDES ====== */
#include "Game.h"
#include "InputModule.h"
#include "CollisionManager.h"
#include "GTUnit.h"
#include "Weapon.h"

#include "Actor.h"

/* ====== DEFINES ====== */
#define ACTOR_DEFAULT_HEALTH 3.0f

#define ACTOR_DEFAULT_UNIT_SPEED_X 0.05f
#define ACTOR_DEFAULT_UNIT_SPEED_Y 0.02f

#define ACTOR_DEFAULT_ATTACK_RATE (1000.0f / 5.0f)

/* ====== VARIABLES ====== */
static const GT_Animation s_aActorAnims[] =
{
    { 0, 2, 1000.0f / 1.0f },
    { 1, 5, 1000.0f / 15.0f },
    { 2, 3, 1000.0f / 5.0f },
    { 3, 3, 1000.0f / 5.0f },
};

/* ====== METHODS ====== */
void Actor::Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_type = ENTITY_TYPE_ACTOR;

    // Defaults
    m_actorState = ACTOR_STATE_IDLE;
    m_actorTeam = ACTOR_TEAM_DEFAULT;

    m_vSpeed = { GTU::UnitToScreenX(ACTOR_DEFAULT_UNIT_SPEED_X),
                 GTU::UnitToScreenY(ACTOR_DEFAULT_UNIT_SPEED_Y) };

    m_health = ACTOR_DEFAULT_HEALTH;
    m_bLookRight = true;

    m_attackRate = ACTOR_DEFAULT_ATTACK_RATE;
    m_pWeapon = nullptr;

    // Init AI stuff
    m_pState = nullptr;
    m_pTask = nullptr;

    // Init default actor animations
    for (i32f i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
        m_aActorAnims[i] = &s_aActorAnims[i];
}

void Actor::Update(f32 dtTime)
{
    if (HandleDeath())
        return;

    HandleState();
    HandleTask();
    HandleCommand(dtTime);
    HandleAnimation(dtTime);
}

b32f Actor::HandleDeath()
{
    if (m_health <= 0)
    {
        WorldEvent event = { WORLD_EVENT_DEATH, this };
        g_game.GetWorld().PushEvent(event);

        g_game.GetWorld().RemoveEntity(this);
        return true;
    }
    return false;
}

void Actor::HandleCommand(f32 dtTime)
{
    // Zero velocity
    m_vVelocity.Zero();

    // If attack state is completed
    if (m_actorState == ACTOR_STATE_ATTACK && m_animElapsed >= m_pAnim->frameDuration)
        m_actorState = ACTOR_STATE_IDLE;

    // Handle command list
    while (!m_lstCommand.IsEmpty())
    {
        GT_Command& cmd = m_lstCommand.Front();
        switch (cmd.cmd)
        {
        case GTC_MOVE_UP:
        case GTC_MOVE_LEFT:
        case GTC_MOVE_DOWN:
        case GTC_MOVE_RIGHT: CommandMove(cmd.cmd, dtTime); break;

        case GTC_ATTACK: CommandAttack(); break;

        default: break;
        }
        m_lstCommand.Pop();
    }

    // Check if we should idle
    if (m_actorState != ACTOR_STATE_ATTACK &&
        !m_vVelocity.x && !m_vVelocity.y)
    {
        m_actorState = ACTOR_STATE_IDLE;
        return;
    }

    // Compute new position
    Vector2 vNewPosition = m_vPosition + m_vVelocity;
    if (m_bCollidable && !g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
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
                // So we'll not move...
                vNewPosition.y -= m_vVelocity.y;
            }
        }
    }

    // Update position
    m_vPosition = vNewPosition;
}

void Actor::CommandMove(s32 cmd, f32 dtTime)
{
    switch (cmd)
    {
    case GTC_MOVE_UP:    m_vVelocity.y -= m_vSpeed.y * dtTime; break;
    case GTC_MOVE_LEFT:  m_vVelocity.x -= m_vSpeed.x * dtTime; break;
    case GTC_MOVE_DOWN:  m_vVelocity.y += m_vSpeed.y * dtTime; break;
    case GTC_MOVE_RIGHT: m_vVelocity.x += m_vSpeed.x * dtTime; break;

    default: break;
    }

    if (m_actorState != ACTOR_STATE_ATTACK)
        m_actorState = ACTOR_STATE_MOVE;
}

void Actor::CommandAttack()
{
    /* We use animations to detect on which state of attack we are */

    // If true then send world event
    b32f bHit = false;

    // If we already attacking
    if (m_actorState == ACTOR_STATE_ATTACK)
    {
        if (m_animElapsed >= m_attackRate)
        {
            m_animElapsed = 0.0f;
            ++m_animFrame;
            if (m_animFrame >= m_pAnim->count)
                m_animFrame = 0;

            bHit = true;
        }
    }
    else
    {
        m_pAnim = m_pWeapon ? m_pWeapon->GetAnimation() : m_aActorAnims[ACTOR_ANIMATION_IDLE];
        m_animFrame = 0;
        m_animElapsed = 0.0f;

        bHit = true;
        m_actorState = ACTOR_STATE_ATTACK;
    }

    // Send world event
    if (bHit)
    {
        // Init
        WorldEvent event;
        event.type = WORLD_EVENT_ATTACK;
        event.attack.pAttacker = this;

        // Push
        g_game.GetWorld().PushEvent(event);
    }
}

void Actor::HandleAnimation(f32 dtTime)
{
    // Check if default animations aren't initialized
    if (!m_aActorAnims[ACTOR_ANIMATION_IDLE])
        return;

    // Set default animation if we don't have
    if (!m_pAnim)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE];
        m_animFrame = 0;
        m_animElapsed = 0.0f;
        return;
    }

    // Update timer
    m_animElapsed += dtTime;

    switch (m_actorState)
    {
    case ACTOR_STATE_IDLE: AnimateIdle(); break;
    case ACTOR_STATE_MOVE: AnimateMove(); break;
    case ACTOR_STATE_ATTACK: AnimateAttack(); return;

    default: g_debugLogMgr.AddNote(CHANNEL_GAME, PR_WARNING, "ACTOR", "HandleAnimation(): Unknown actor state: %d", m_actorState); break;
    }

    // Update frame
    if (m_animElapsed >= m_pAnim->frameDuration)
    {
        m_animElapsed = 0.0f;
        ++m_animFrame;
    }

    // Loop animation and reset new animations with smaller count
    if (m_animFrame >= m_pAnim->count)
        m_animFrame = 0;
}

void Actor::AnimateIdle()
{
    m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE];

    m_flip = m_bLookRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Actor::AnimateMove()
{
    if (m_vVelocity.x > 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_MOVE_HORIZONTAL];

        m_bLookRight = true;
        m_flip = SDL_FLIP_NONE;
    }
    else if (m_vVelocity.x < 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_MOVE_HORIZONTAL];

        m_bLookRight = false;
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    else if (m_vVelocity.y > 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_BOTTOM];

        m_flip = SDL_FLIP_NONE;
    }
    else if (m_vVelocity.y < 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_TOP];

        m_flip = SDL_FLIP_NONE;
    }
}

void Actor::AnimateAttack()
{
    // Check if we need flip
    if (m_vVelocity.x > 0)
    {
        m_bLookRight = true;
        m_flip = SDL_FLIP_NONE;
    }
    else if (m_vVelocity.x < 0)
    {
        m_bLookRight = false;
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        m_flip = m_bLookRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    }
}
